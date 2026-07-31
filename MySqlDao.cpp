#include "stdafx.h"
#include "MySqlDao.h"
#include "BoostLog.h"
#include "MySqlDaoDll.h"

#define _MES_DATA_BASE_VERSION_NUMBER_ 1
#define _MES_MYSQL_DLL_VERSION_NUMBER_ "1.1.0.1"

// 静态成员初始化
bool CMySqlDao::m_upgradeInProgress = false;
HANDLE CMySqlDao::m_upgradeThread = NULL;
CString CMySqlDao::m_upgradeHost = _T("");
CString CMySqlDao::m_upgradeUser = _T("");
CString CMySqlDao::m_upgradePwd = _T("");
CString CMySqlDao::m_upgradeDb = _T("");
int CMySqlDao::m_upgradePort = 3306;

CMySqlDao::CMySqlDao() : m_mysql(NULL), m_versionChecked(false) {}

CMySqlDao::~CMySqlDao() { Disconnect(); }

bool CMySqlDao::IsConnected()
{
	CSingleLock lock(&m_cs, TRUE);
	return m_mysql != NULL;
}

bool CMySqlDao::Connect(const char* host, const char* user, const char* pwd, const char* db, int port)
{
	CSingleLock lock(&m_cs, TRUE);

	if (m_mysql) mysql_close(m_mysql);

	m_mysql = mysql_init(NULL);

	// 设置自动重连（防呆/稳定性）
	int reconnect = 1;
	mysql_options(m_mysql, MYSQL_OPT_RECONNECT, &reconnect);

	// 编码设置
	mysql_options(m_mysql, MYSQL_SET_CHARSET_NAME, "gbk");

	if (!mysql_real_connect(m_mysql, CT2A(host), CT2A(user), CT2A(pwd), CT2A(db), port, NULL, 0))
	{
		CString sErr;
		sErr.Format("%s", mysql_error(m_mysql));
		m_strError.Format("Connect Error: %s", sErr);
		//m_strError.Format(_T("Connect Error: %S"), mysql_error(m_mysql));
		LogInfo(m_strError);
		return false;
	}

	// 保存连接信息供升级线程使用
	m_upgradeHost = host;
	m_upgradeUser = user;
	m_upgradePwd = pwd;
	m_upgradeDb = db;
	m_upgradePort = port;

	// 检查和管理数据库版本（首次连接时执行）
	if (!CheckAndManageVersion()) {
		mysql_close(m_mysql);
		m_mysql = NULL;
		return false;
	}

	//LogInfo(_T("Connected to database: %s"), db);
	Print(Info, "Connected to database: %s", db);
	return true;
}

void CMySqlDao::Disconnect()
{
	CSingleLock lock(&m_cs, TRUE);
	if (m_mysql) {
		mysql_close(m_mysql);
		m_mysql = NULL;
	}
	m_versionChecked = false;
}

int CMySqlDao::ExecuteSql(const char* lpSql)
{
	CSingleLock lock(&m_cs, TRUE);
	if(lpSql == "")
		return -1;
	if (!m_mysql) 
		return -1;
	CString sSQL;
	sSQL.Format("%s", lpSql);
	Print(Info, "SQL: " + sSQL);

	if (mysql_query(m_mysql, CT2A(lpSql))) {
		CString sErr;
		sErr.Format("%s", mysql_error(m_mysql));
		m_strError.Format("SQL Exec Error: %s", sErr);
		LogInfo(m_strError + _T(" | SQL: ") + lpSql);
		//m_strError.Format(_T("SQL Exec Error: %s"), mysql_error(m_mysql));
		//Log(m_strError + _T(" | SQL: ") + lpSql);
		return -1;
	}
	return (int)mysql_affected_rows(m_mysql);
}

//bool CMySqlDao::Upsert(LPCTSTR strTableName, const MySQLDataMap& data)
//{
//	if (data.empty()) return false;
//
//	CString strCols, strVals, strUpdate;
//	for (auto const& item : data) {
//		CString key = item.first;
//		CString val = item.second;
//		val.Replace(_T("'"), _T("''")); // 基础防SQL注入转义
//
//		strCols += _T("`") + key + _T("`,");
//		strVals += _T("'") + val + _T("',");
//		strUpdate += _T("`") + key + _T("`='") + val + _T("',");
//	}
//	strCols.TrimRight(_T(","));
//	strVals.TrimRight(_T(","));
//	strUpdate.TrimRight(_T(","));
//
//	// 使用 MySQL 特有的 ON DUPLICATE KEY UPDATE 语法
//	CString strSql;
//	strSql.Format(_T("INSERT INTO `%s` (%s) VALUES (%s) ON DUPLICATE KEY UPDATE %s"),
//		strTableName, strCols, strVals, strUpdate);
//
//	return ExecuteSql(strSql) != -1;
//}

bool CMySqlDao::ExecuteUpsert(
	const char* strTableName,
	const ParamMap& dataMap,
	const UniqueKeyList& businessKeys
	)
{
    CSingleLock lock(&m_cs, TRUE);
	if (!m_mysql) {
		m_strError = _T("ExecuteUpsert Failed: Not connected to database.");
		LogInfo(m_strError);
		return false;
	}
	if (dataMap.empty()) {
		m_strError = _T("ExecuteUpsert Failed: Data map is empty.");
		LogInfo(m_strError);
		return false;
	}

	// 1) 检查表是否存在
	CString escTable = EscapeString(CString(strTableName));
	CString chkSql;
	chkSql.Format(_T("SHOW TABLES LIKE '%s'"), escTable);
	std::vector<std::vector<CString>> res;
	if (!QuerySql(CT2A(chkSql), res)) {
		// QuerySql 已设置 m_strError
		return false;
	}

	if (res.empty()) {
		// 表不存在，尝试创建
		if (!CreateTable(strTableName)) {
			// CreateTable 应设置 m_strError
			return false;
		}
	}

	// 业务唯一键集合
	std::set<CString> businessKeySet(businessKeys.begin(), businessKeys.end());

	CString strFields, strValues, strUpdate;
	bool hasUpdateField = false;

	for (auto const& item : dataMap) {
		CString key = item.first;
		CString val = item.second;

		// 1. 永远忽略 id（自增主键不参与 UPSERT）
		//if (key.CompareNoCase(_T("id")) == 0)
		//	continue;

		// 2. 转义
		val.Replace(_T("'"), _T("''"));

		// INSERT 字段
		strFields += _T("`") + key + _T("`,");
		strValues += _T("'") + val + _T("',");

		// 3. UPDATE 只允许“非业务键”
		if (businessKeySet.find(key) == businessKeySet.end()) {
			strUpdate += _T("`") + key + _T("`=VALUES(`") + key + _T("`),");
			hasUpdateField = true;
		}
	}

	strFields.TrimRight(_T(","));
	strValues.TrimRight(_T(","));
	strUpdate.TrimRight(_T(","));

	if (strFields.IsEmpty() || strValues.IsEmpty()) {
		m_strError = _T("ExecuteUpsert Failed: No valid fields.");
		LogInfo(m_strError);
		return false;
	}

	// 防止 UPDATE 子句为空（MySQL 语法要求）
	if (!hasUpdateField) {
		// 使用任意一个非业务字段进行“空更新”，先校验 businessKeys
		if (!businessKeys.empty()) {
			CString key = businessKeys.front();
			strUpdate.Format(_T("`%s`=`%s`"), key, key);
		} else {
			m_strError = _T("ExecuteUpsert Failed: No updateable fields and businessKeys empty.");
			LogInfo(m_strError);
			return false;
		}
	}

	CString strSql;
	strSql.Format(
		_T("INSERT INTO `%s` (%s) VALUES (%s) ON DUPLICATE KEY UPDATE %s"),
		strTableName,
		strFields,
		strValues,
		strUpdate
		);

	return ExecuteSql(strSql) != -1;
}


bool CMySqlDao::QuerySql(const char* lpSql, std::vector<std::vector<CString>>& outResults)
{
	CSingleLock lock(&m_cs, TRUE);
	outResults.clear();

	if (mysql_query(m_mysql, CT2A(lpSql))) {
		CString sErr;
		sErr.Format("%s", mysql_error(m_mysql));
		m_strError.Format("Query Error: %s", sErr);
		//m_strError.Format(_T("Query Error: %S"), mysql_error(m_mysql));
		return false;
	}

	MYSQL_RES* res = mysql_store_result(m_mysql);
	if (!res) return true;

	int num_fields = mysql_num_fields(res);
	MYSQL_ROW row;
	while ((row = mysql_fetch_row(res))) {
		std::vector<CString> rowData;
		for (int i = 0; i < num_fields; i++) {
			rowData.push_back(row[i] ? CString(row[i]) : _T(""));
		}
		outResults.push_back(rowData);
	}
	mysql_free_result(res);
	return true;
}

int CMySqlDao::DeleteByConditions(const char* strTableName, const ParamMap& conditionMap)
{
	CSingleLock lock(&m_cs, TRUE);

	if (!strTableName || strTableName[0] == '\0') {
		m_strError = _T("DeleteByConditions Failed: Table name is empty.");
		LogInfo(m_strError);
		return -1;
	}

	if (conditionMap.empty()) {
		m_strError = _T("DeleteByConditions Failed: conditionMap is empty.");
		LogInfo(m_strError);
		return -1;
	}

	if (!m_mysql) {
		m_strError = _T("DeleteByConditions Failed: Not connected to database.");
		LogInfo(m_strError);
		return -1;
	}

	CString strWhere;
	for (const auto& item : conditionMap) {
		CString key = item.first;
		CString escVal = EscapeString(item.second);
		strWhere += _T("`") + key + _T("`='") + escVal + _T("' AND ");
	}

	if (strWhere.IsEmpty()) {
		m_strError = _T("DeleteByConditions Failed: No valid conditions.");
		LogInfo(m_strError);
		return -1;
	}
	strWhere = strWhere.Left(strWhere.GetLength() - 5);

	CString strSql;
	strSql.Format(_T("DELETE FROM `%s` WHERE %s"), strTableName, strWhere);

	int affectedRows = ExecuteSql(CT2A(strSql));
	if (affectedRows == -1) {
		LogInfo(m_strError + _T(" | SQL: ") + strSql);
	}

	return affectedRows;
}

void CMySqlDao::LogInfo(LPCTSTR fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	CString strLog;
	strLog.FormatV(fmt, args);
	va_end(args);

	//OutputDebugString(_T("[MySQL_DAO] ") + strLog + _T("\n"));
	Print(Error, "[MySQL_DAO] %s", strLog);
}

unsigned long long CMySqlDao::GetLastInsertId()
{
	CSingleLock lock(&m_cs, TRUE);
	if (!m_mysql) return 0;
	return (unsigned long long)mysql_insert_id(m_mysql); // mysql_insert_id 返回 my_ulonglong
}

unsigned long long CMySqlDao::ExecuteUpsertAndGetId(const char* strTableName,
	const ParamMap& dataMap,
	const UniqueKeyList& businessKeys)
{
    CSingleLock lock(&m_cs, TRUE);

	if (dataMap.empty()) {
		m_strError = _T("ExecuteUpsertAndGetId Failed: Data map is empty.");
		LogInfo(m_strError);
		return 0;
	}

	// 1) 检查表是否存在
	CString escTable = EscapeString(CString(strTableName));
	CString chkSql;
	chkSql.Format(_T("SHOW TABLES LIKE '%s'"), escTable);
	std::vector<std::vector<CString>> res;
	if (!QuerySql(CT2A(chkSql), res)) {
		// QuerySql 已设置 m_strError
		return false;
	}

	if (res.empty()) {
		// 表不存在，尝试创建
		if (!CreateTable(strTableName)) {
			// CreateTable 应设置 m_strError
			return false;
		}
	}

	std::set<CString> businessSet;
	for (const auto& k : businessKeys) {
		CString low = k;
		low.MakeLower();
		businessSet.insert(low);
	}

	CString strFields, strValues, strUpdate;
	for (auto const& item : dataMap) {
		CString key = item.first;
		CString val = item.second;

		if (key.CompareNoCase(_T("id")) == 0) continue;

		val.Replace(_T("'"), _T("''"));

		strFields += _T("`") + key + _T("`,");
		strValues += _T("'") + val + _T("',");

		CString lowKey = key; lowKey.MakeLower();
		if (businessSet.find(lowKey) == businessSet.end()) {
			strUpdate += _T("`") + key + _T("`=VALUES(`") + key + _T("`),");
		}
	}

	strFields.TrimRight(_T(","));
	strValues.TrimRight(_T(","));
	strUpdate.TrimRight(_T(","));

	if (strFields.IsEmpty() || strValues.IsEmpty()) {
		m_strError = _T("ExecuteUpsertAndGetId Failed: No valid fields.");
		LogInfo(m_strError);
		return 0;
	}

	CString updateClause;
	if (!strUpdate.IsEmpty()) {
		updateClause = _T("`id`=LAST_INSERT_ID(`id`),") + strUpdate;
	}
	else {
		updateClause = _T("`id`=LAST_INSERT_ID(`id`)");
	}

	CString strSql;
	strSql.Format(
		_T("INSERT INTO `%s` (%s) VALUES (%s) ON DUPLICATE KEY UPDATE %s;"),
		strTableName, strFields, strValues, updateClause);

	if (ExecuteSql(strSql) == -1) {
		LogInfo(m_strError + _T(" | SQL: ") + strSql);
		return 0;
	}

	unsigned long long id = GetLastInsertId();
	return id;
}

__declspec(dllexport) CMySqlDao* CreateMysql()
{
	return new CMySqlDao();
}

// CreateTable: 根据表名使用预定义建表语句创建表（若支持的表名之一）。
bool CMySqlDao::CreateTable(const char* strTableName)
{
	CSingleLock lock(&m_cs, TRUE);

	if (!strTableName || strTableName[0] == '\0') {
		m_strError = _T("CreateTable Failed: Table name is empty.");
		LogInfo(m_strError);
		return false;
	}

	if (!m_mysql) {
		m_strError = _T("CreateTable Failed: Not connected to database.");
		LogInfo(m_strError);
		return false;
	}

	CString sTable = strTableName;
	sTable.MakeLower();
	int nIndex = sTable.ReverseFind('_');
	if (nIndex != -1)
	{
		sTable = sTable.Left(nIndex);
	}

	CString sSql;
	if (sTable == _T("machine")) {
		sSql = _T("CREATE TABLE `machine` (\n"
			"  `id` int(11) NOT NULL COMMENT '机台号',\n"
			"  `machine_name` varchar(255) COLLATE utf8mb4_unicode_ci DEFAULT NULL COMMENT '机台名称',\n"
			"  `procedure` varchar(255) COLLATE utf8mb4_unicode_ci DEFAULT NULL COMMENT '工序',\n"
			"  `job_path` varchar(255) COLLATE utf8mb4_unicode_ci DEFAULT NULL COMMENT 'job路径',\n"
			"  `car_path` varchar(255) COLLATE utf8mb4_unicode_ci DEFAULT NULL COMMENT 'car路径',\n"
			"  `log_path` varchar(255) COLLATE utf8mb4_unicode_ci DEFAULT NULL COMMENT 'log路径',\n"
			"  `qr_path` varchar(255) COLLATE utf8mb4_unicode_ci DEFAULT NULL COMMENT '二维码路径',\n"
			"  `precision` double DEFAULT NULL COMMENT '机台精度',\n"
			"  `fm_path` varchar(255) COLLATE utf8mb4_unicode_ci DEFAULT NULL COMMENT 'FM路径',\n"
			"  `true_point_rate` double DEFAULT NULL,\n"
			"  PRIMARY KEY(`id`) USING BTREE,\n"
			"  UNIQUE KEY `machine_machine_name_IDX` (`machine_name`) USING BTREE\n"
			") ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;");
	}
	else if (sTable == _T("job")) {
		sSql = _T("CREATE TABLE `job` (\n"
			"  `id` INT(11) NOT NULL AUTO_INCREMENT,\n"
			"  `job_name` VARCHAR(255) COLLATE utf8mb4_unicode_ci NOT NULL COMMENT '料号名',\n"
			"  `procedure` VARCHAR(255) COLLATE utf8mb4_unicode_ci DEFAULT NULL COMMENT '工序',\n"
			"  `surface_id` INT(11) DEFAULT NULL COMMENT '膜面id(模板id)',\n"
			"  `machine_id` INT(11) NOT NULL,\n"
			"  `surface_name` varchar(255) COLLATE utf8mb4_unicode_ci DEFAULT NULL,\n"
			"  PRIMARY KEY(`id`),\n"
			"  UNIQUE KEY `idx_machine_id_job_name` (`machine_id`, `job_name`)\n"
			") ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;");
	}
	else if (sTable == _T("decode")) {
		sSql = _T("CREATE TABLE `decode` (\n"
			"  `id` INT(11) NOT NULL AUTO_INCREMENT,\n"
			"  `decode` VARCHAR(255) COLLATE utf8mb4_unicode_ci NOT NULL COMMENT '二维码',\n"
			"  `test_date` VARCHAR(255) COLLATE utf8mb4_unicode_ci DEFAULT NULL COMMENT '测试日期',\n"
			"  `test_id` INT(11) DEFAULT NULL COMMENT '测试id',\n"
			"  `side` VARCHAR(255) COLLATE utf8mb4_unicode_ci DEFAULT NULL,\n"
			"  PRIMARY KEY(`id`)\n"
			") ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;");
	}
	else if (sTable == _T("tab_err")) {
		sSql.Format("CREATE TABLE `%s` (\n"
			"  `id` int(11) NOT NULL AUTO_INCREMENT COMMENT '技术主键，自增',\n"
			"  `test_machine_id` int(11) NOT NULL COMMENT '测试机台号',\n"
			"  `job_name` varchar(255) CHARACTER SET utf8 NOT NULL COMMENT '料号',\n"
			"  `plno` varchar(255) CHARACTER SET utf8 NOT NULL COMMENT '批量号',\n"
			"  `pcbno` int(11) NOT NULL COMMENT '板号',\n"
			"  `is_top` tinyint(1) NOT NULL COMMENT '正反面(1为正面)',\n"
			"  `err_index` int(11) NOT NULL COMMENT '缺陷序号',\n"
			"  `stack_id` int(20) NOT NULL,\n"
			"  `pointx` int(11) DEFAULT NULL COMMENT '缺陷坐标x',\n"
			"  `pointy` int(11) DEFAULT NULL COMMENT '缺陷坐标y',\n"
			"  `area` float(10,2) DEFAULT NULL COMMENT '缺陷大小',\n"
			"  `vrs_result` tinyint(1) NOT NULL DEFAULT '0' COMMENT '0默认，1NG 2OK',\n"
			"  `ai_result` tinyint(1) NOT NULL DEFAULT '0' COMMENT '0默认，1NG 2OK',\n"
			"  `recheck_result` tinyint(1) NOT NULL DEFAULT '0' COMMENT '0默认，1NG    2OK',\n"
			"  `err_type` varchar(45) CHARACTER SET utf8 DEFAULT NULL COMMENT '缺陷类型',\n"
			"  `err_level` int(11) DEFAULT NULL COMMENT '缺陷等级',\n"
			"  `unit_id` int(11) DEFAULT NULL COMMENT '单元ID',\n"
			"  `serial_no` varchar(45) CHARACTER SET utf8 DEFAULT NULL,\n"
			"  `pos_num` varchar(45) CHARACTER SET utf8 DEFAULT NULL,\n"
			"  `identy_num` varchar(45) CHARACTER SET utf8 DEFAULT NULL,\n"
			"  `unit_name` varchar(45) CHARACTER SET utf8 DEFAULT NULL COMMENT '单元号',\n"
			"  `err_edit_type_id` int(11) DEFAULT NULL,\n"
			"  `err_edit_type_name` varchar(45) CHARACTER SET utf8 DEFAULT NULL,\n"
			"  `ai_err_type` varchar(255) CHARACTER SET utf8 DEFAULT NULL,\n"
			"  `ai_err_level` varchar(255) CHARACTER SET utf8 DEFAULT NULL,\n"
			"  `err_TestOffsetX` int(11) DEFAULT NULL,\n"
			"  `err_TestOffsetY` int(11) DEFAULT NULL,\n"
			"  `err_ImagePath` varchar(255) CHARACTER SET utf8 DEFAULT NULL COMMENT '缺陷图片路径',\n"
			"  `recheck_ImagePath` varchar(255) DEFAULT NULL COMMENT 'VRS图片路径',\n"
			"  `surface` varchar(255) CHARACTER SET utf8 DEFAULT NULL COMMENT '膜面',\n"
			"  `length` int(11) DEFAULT NULL COMMENT '长度',\n"
			"  `size` double DEFAULT NULL COMMENT '面积',\n"
			"  `confidence_interval` double DEFAULT NULL COMMENT '置信度',\n"
			"  `size_ratio` double DEFAULT NULL COMMENT '面积比',\n"
			"  `area_type` varchar(255) CHARACTER SET utf8 DEFAULT NULL COMMENT '区域类型',\n"
			"  `classify` varchar(255) CHARACTER SET utf8 DEFAULT NULL COMMENT '类型',\n"
			"  `model` varchar(255) CHARACTER SET utf8 DEFAULT NULL COMMENT '模型',\n"
			"  `ai_aoi_temp` varchar(255) CHARACTER SET utf8 DEFAULT NULL COMMENT 'ai模板',\n"
			"  `update_time` datetime DEFAULT NULL COMMENT '更新时间',\n"
			"  `layer_name` varchar(100) DEFAULT NULL COMMENT '层别',\n"
			"  `maxOf1stConf` double DEFAULT NULL COMMENT '第一帧最大置信度',\n"
			"  `maxOf2ndConf` double DEFAULT NULL,\n"
			"  `maxOf3rdConf` double DEFAULT NULL,\n"
			"  `pointx_mm` double DEFAULT NULL COMMENT 'x毫米坐标',\n"
			"  `pointy_mm` double DEFAULT NULL COMMENT 'y毫米坐标',\n"
			"  PRIMARY KEY(`id`) USING BTREE,\n"
			"  UNIQUE KEY `uk_tab_err_business` (`test_machine_id`,`job_name`,`plno`,`pcbno`,`is_top`,`err_index`) USING BTREE,\n"
			"  KEY `idx_stack_id_pcb_no` (`stack_id`,`pcbno`)\n"
			") ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 ROW_FORMAT=DYNAMIC COMMENT='缺陷表，id自增+业务唯一键';", strTableName);
	}
	else if (sTable == _T("tab_test")) {
		sSql.Format("CREATE TABLE `%s` (\n"
			"  `id` int(11) NOT NULL AUTO_INCREMENT COMMENT '技术主键',\n"
			"  `test_machine_id` int(11) NOT NULL COMMENT '测试设备ID',\n"
			"  `job_name` varchar(45) CHARACTER SET utf8 NOT NULL COMMENT '料号',\n"
			"  `plno` varchar(45) CHARACTER SET utf8 NOT NULL COMMENT '批量号',\n"
			"  `pcbno` int(11) NOT NULL COMMENT '板号',\n"
			"  `is_top` tinyint(1) NOT NULL COMMENT '正反面(1:正面 0:反面)',\n"
			"  `stack_id` int(11) NOT NULL,\n"
			"  `decode` varchar(45) CHARACTER SET utf8 DEFAULT NULL COMMENT '二维码',\n"
			"  `decodes` varchar(200) CHARACTER SET utf8 DEFAULT NULL COMMENT '二维码数组',\n"
			"  `penma_id` varchar(100) CHARACTER SET utf8 DEFAULT NULL COMMENT '喷码号',\n"
			"  `customer_no` varchar(45) CHARACTER SET utf8 DEFAULT NULL COMMENT '客户编号',\n"
			"  `npi` tinyint(1) DEFAULT NULL,\n"
			"  `layer_name` varchar(45) CHARACTER SET utf8 DEFAULT NULL COMMENT '层别',\n"
			"  `errnum` int(11) DEFAULT NULL COMMENT '缺陷数量',\n"
			"  `err_path` varchar(300) CHARACTER SET utf8 DEFAULT NULL COMMENT '缺陷路径',\n"
			"  `test_machine_code` varchar(255) CHARACTER SET utf8 DEFAULT NULL COMMENT '测试设备编码',\n"
			"  `test_person` varchar(20) CHARACTER SET utf8 DEFAULT NULL COMMENT '测试人员',\n"
			"  `test_time` datetime DEFAULT NULL COMMENT '测试时间',\n"
			"  `test_result` tinyint(1) DEFAULT NULL COMMENT '测试结果',\n"
			"  `verify_machine_id` int(11) DEFAULT NULL COMMENT '检修设备ID',\n"
			"  `verify_machine_code` varchar(45) CHARACTER SET utf8 DEFAULT NULL COMMENT '检修设备编码',\n"
			"  `verify_person` varchar(20) CHARACTER SET utf8 DEFAULT NULL COMMENT '检修人员',\n"
			"  `verify_time` datetime DEFAULT NULL COMMENT '检修时间',\n"
			"  `verify_result` tinyint(1) DEFAULT NULL COMMENT '检修结果',\n"
			"  `high_risk_defect_num` int(11) DEFAULT NULL COMMENT 'ai严重缺陷数量  ',\n"
			"  `panel_len` decimal(10,3) unsigned zerofill DEFAULT '0000000.000' COMMENT '板长',\n"
			"  `panel_width` decimal(10,3) unsigned zerofill DEFAULT '0000000.000' COMMENT '板宽',\n"
			"  `ai_true_num` int(11) DEFAULT NULL COMMENT 'ai报点数     (ai 报缺陷数，  nullai软件没跑)',\n"
			"  `ai_missing_num` int(11) DEFAULT NULL COMMENT 'ai漏失数              （检修机写）  ai ok    人工ng 的点数',\n"
			"  `surface` int(11) DEFAULT NULL COMMENT '膜面（表面处理）',\n"
			"  `ai_run_time` varchar(255) CHARACTER SET utf8 DEFAULT NULL COMMENT 'ai跑板时间',\n"
			"  `job_path` varchar(255) CHARACTER SET utf8 DEFAULT NULL COMMENT 'job路径',\n"
			"  `car_path` varchar(255) CHARACTER SET utf8 DEFAULT NULL COMMENT 'car路径',\n"
			"  `log_path` varchar(255) CHARACTER SET utf8 DEFAULT NULL COMMENT 'log路径',\n"
			"  `std_path` varchar(255) CHARACTER SET utf8 DEFAULT NULL COMMENT '标准板路径',\n"
			"  `study_path` varchar(255) CHARACTER SET utf8 DEFAULT NULL COMMENT '学板路径',\n"
			"  `ai_aoi_temp` varchar(255) CHARACTER SET utf8 DEFAULT NULL COMMENT 'ai-aoi模板',\n"
			"  `ai_aoi_model` varchar(255) CHARACTER SET utf8 DEFAULT NULL COMMENT 'ai-aoi模型类别',\n"
			"  `update_time` datetime DEFAULT NULL COMMENT '更新时间',\n"
			"  PRIMARY KEY(`id`),\n"
			"  UNIQUE KEY `uk_tab_test_business` (`job_name`,`plno`,`pcbno`,`is_top`,`test_machine_id`),\n"
			"  UNIQUE KEY `idx_stack_id_pcb_no_is_top` (`stack_id`,`pcbno`,`is_top`) USING BTREE\n"
			") ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;", strTableName);
	}
	else if (sTable == _T("stack")) {
		sSql = _T("CREATE TABLE `stack` (\n"
			"  `id` int(11) NOT NULL AUTO_INCREMENT,\n"
			"  `pl_name` varchar(255) COLLATE utf8mb4_unicode_ci NOT NULL COMMENT '料号全称',\n"
			"  `machine_id` int(11) NOT NULL COMMENT '机台号',\n"
			"  `test_date` varchar(255) COLLATE utf8mb4_unicode_ci NOT NULL COMMENT '测试日期',\n"
			"  `job_name` varchar(255) COLLATE utf8mb4_unicode_ci NOT   NULL COMMENT '料号',\n"
			"  `lot_name` varchar(255) COLLATE utf8mb4_unicode_ci NOT NULL COMMENT 'lot号',\n"
			"  `create_time` datetime DEFAULT NULL COMMENT '创建时间',\n"
			"  `update_time` datetime NOT NULL COMMENT '更新时间',\n"
			"  `layer_names` varchar(255) COLLATE utf8mb4_unicode_ci DEFAULT NULL,\n"
			"  PRIMARY KEY(`id`),\n"
			"  UNIQUE KEY `idx_machine_date_job_pl` (`pl_name`,`machine_id`,`test_date`,`job_name`) USING BTREE,\n"
			"  KEY `idx_machine_id` (`machine_id`)\n"
			") ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;");
	}
	else {
		m_strError.Format(_T("CreateTable Failed: unsupported table '%s'"), strTableName);
		LogInfo(m_strError);
		return false;
	}

	// 执行建表语句
	if (ExecuteSql(CT2A(sSql)) == -1) {
		LogInfo(m_strError + _T(" | SQL: ") + sSql);
		return false;
	}

	return true;
}

bool CMySqlDao::EnsureTableAndUpsert(const char* strTableName, const ParamMap& dataMap, const UniqueKeyList& businessKeys)
{
	CSingleLock lock(&m_cs, TRUE);

	if (!strTableName || strTableName[0] == '\0') {
		m_strError = _T("EnsureTableAndUpsert Failed: Table name is empty.");
		LogInfo(m_strError);
		return false;
	}

	if (dataMap.empty()) {
		m_strError = _T("EnsureTableAndUpsert Failed: dataMap is empty.");
		LogInfo(m_strError);
		return false;
	}

	// 1) 检查表是否存在
	CString escTable = EscapeString(CString(strTableName));
	CString chkSql;
	chkSql.Format(_T("SHOW TABLES LIKE '%s'"), escTable);
	std::vector<std::vector<CString>> res;
	if (!QuerySql(CT2A(chkSql), res)) {
		// QuerySql 已设置 m_strError
		return false;
	}

	if (res.empty()) {
		// 表不存在，尝试创建
		if (!CreateTable(strTableName)) {
			// CreateTable 应设置 m_strError
			return false;
		}
	}

	// 2) 构造 INSERT ... ON DUPLICATE KEY UPDATE
	CString strFields, strValues, strUpdate;

	// 统一 businessKeys 的字段名为小写集合以便比较
	std::set<CString> businessKeySet;
	for (const auto& k : businessKeys) {
		CString low = k;
		low.MakeLower();
		businessKeySet.insert(low);
	}

	for (auto const& item : dataMap) {
		CString key = item.first;
		CString val = item.second;
		CString escVal = EscapeString(val);

		strFields += _T("`") + key + _T("`,");
		strValues += _T("'") + escVal + _T("',");

		CString lowKey = key;
		lowKey.MakeLower();
		// 如果该字段不是 businessKeys 中的字段，则作为更新字段
		if (businessKeySet.find(lowKey) == businessKeySet.end()) {
			strUpdate += _T("`") + key + _T("`=VALUES(`") + key + _T("`),");
		}
	}

	strFields.TrimRight(_T(","));
	strValues.TrimRight(_T(","));
	strUpdate.TrimRight(_T(","));

	if (strFields.IsEmpty() || strValues.IsEmpty()) {
		m_strError = _T("EnsureTableAndUpsert Failed: No valid fields to insert.");
		LogInfo(m_strError);
		return false;
	}

	if (strUpdate.IsEmpty()) {
		// 如果没有可更新字段，使用 businessKeys 的任意一个字段做空更新以满足语法
		if (!businessKeys.empty()) {
			CString key = businessKeys.front();
			strUpdate.Format(_T("`%s`=`%s`"), key, key);
		} else {
			m_strError = _T("EnsureTableAndUpsert Failed: No update fields and businessKeys empty.");
			LogInfo(m_strError);
			return false;
		}
	}

	CString strSql;
	strSql.Format(_T("INSERT INTO `%s` (%s) VALUES (%s) ON DUPLICATE KEY UPDATE %s"),
		strTableName, strFields, strValues, strUpdate);

	return ExecuteSql(CT2A(strSql)) != -1;
}

CString CMySqlDao::EscapeString(const CString& src) const
{
	if (!m_mysql) return src;

	// mysql_real_escape_string 要求目标缓冲区至少为 src_len*2 + 1
	size_t len = src.GetLength();
	std::vector<char> buf(len * 2 + 1);

	// 将 CString 转为 UTF-8/ANSI 根据编译设置：CT2A 在库中使用过，这里直接按 ANSI 处理
	CT2A conv(src);
	unsigned long long written = mysql_real_escape_string(m_mysql, buf.data(), conv, (unsigned long)strlen(conv));
	CString out;
	out = CA2T(buf.data());
	return out;
}

// Provide C-style exported wrappers so callers using LoadLibrary/GetProcAddress
// can obtain unmangled function names like "Connect". These forward to a
// singleton CMySqlDao instance.
static CMySqlDao* g_pGlobalDao = nullptr;

extern "C" {
	MYSQLDAO_API bool Connect(const char* host, const char* user, const char* pwd, const char* db, int port)
	{
		if (!g_pGlobalDao) g_pGlobalDao = new CMySqlDao();
		return g_pGlobalDao->Connect(host, user, pwd, db, port);
	}

	MYSQLDAO_API void Disconnect()
	{
		if (g_pGlobalDao) {
			g_pGlobalDao->Disconnect();
			delete g_pGlobalDao;
			g_pGlobalDao = nullptr;
		}
	}

	MYSQLDAO_API bool IsConnected()
	{
		if (!g_pGlobalDao) return false;
		return g_pGlobalDao->IsConnected();
	}

	MYSQLDAO_API bool ExecuteUpsert(const char* strTableName,
		const ParamMap& dataMap,
		const UniqueKeyList& uniqueKeys)
	{
		if (!g_pGlobalDao) g_pGlobalDao = new CMySqlDao();
		return g_pGlobalDao->ExecuteUpsert(strTableName, dataMap, uniqueKeys);
	}

	MYSQLDAO_API unsigned long long ExecuteUpsertAndGetId(const char* strTableName,
		const ParamMap& dataMap,
		const UniqueKeyList& businessKeys)
	{
		if (!g_pGlobalDao) g_pGlobalDao = new CMySqlDao();
		return g_pGlobalDao->ExecuteUpsertAndGetId(strTableName, dataMap, businessKeys);
	}

	MYSQLDAO_API int ExecuteSql(const char* lpSql)
	{
		if (!g_pGlobalDao) g_pGlobalDao = new CMySqlDao();
		return g_pGlobalDao->ExecuteSql(lpSql);
	}

	MYSQLDAO_API bool QuerySql(const char* lpSql, std::vector<std::vector<CString>>& outResults)
	{
		if (!g_pGlobalDao) g_pGlobalDao = new CMySqlDao();
		return g_pGlobalDao->QuerySql(lpSql, outResults);
	}

	MYSQLDAO_API int DeleteByConditions(const char* strTableName, const ParamMap& conditionMap)
	{
		if (!g_pGlobalDao) g_pGlobalDao = new CMySqlDao();
		return g_pGlobalDao->DeleteByConditions(strTableName, conditionMap);
	}

	MYSQLDAO_API bool EnsureTableAndUpsert(const char* strTableName, const ParamMap& dataMap, const UniqueKeyList& businessKeys)
	{
		if (!g_pGlobalDao) g_pGlobalDao = new CMySqlDao();
		return g_pGlobalDao->EnsureTableAndUpsert(strTableName, dataMap, businessKeys);
	}

	MYSQLDAO_API bool EnsureTableAndUpsertBatch(const char* strTableName, const std::vector<ParamMap>& rows, const UniqueKeyList& businessKeys, size_t batchSize)
	{
		if (!g_pGlobalDao) g_pGlobalDao = new CMySqlDao();
		return g_pGlobalDao->EnsureTableAndUpsertBatch(strTableName, rows, businessKeys, batchSize);
	}
}

bool CMySqlDao::EnsureTableAndUpsertBatch(const char* strTableName, const std::vector<ParamMap>& rows, const UniqueKeyList& businessKeys, size_t batchSize)
{
	CSingleLock lock(&m_cs, TRUE);

	if (!strTableName || strTableName[0] == '\0') {
		m_strError = _T("EnsureTableAndUpsertBatch Failed: Table name is empty.");
		LogInfo(m_strError);
		return false;
	}

	if (rows.empty()) {
		m_strError = _T("EnsureTableAndUpsertBatch Failed: rows is empty.");
		LogInfo(m_strError);
		return false;
	}

	if (!m_mysql) {
		m_strError = _T("EnsureTableAndUpsertBatch Failed: Not connected to database.");
		LogInfo(m_strError);
		return false;
	}

	// 缓存表存在判断，减少 SHOW TABLES 调用
	CString tableNameCs = CString(strTableName);
	CString tableNameLower = tableNameCs;
	tableNameLower.MakeLower();
	if (m_existingTablesCache.find(tableNameLower) == m_existingTablesCache.end()) {
		// 检查表是否存在
		CString escTable = EscapeString(tableNameCs);
		CString chkSql;
		chkSql.Format(_T("SHOW TABLES LIKE '%s'"), escTable);
		std::vector<std::vector<CString>> res;
		if (!QuerySql(CT2A(chkSql), res)) {
			return false; // QuerySql 已设置 m_strError
		}
		if (res.empty()) {
			if (!CreateTable(strTableName)) {
				return false; // CreateTable 设置 m_strError
			}
		}
		m_existingTablesCache.insert(tableNameLower);
	}

	// 统一 businessKeys 的字段名为小写集合以便比较
	std::set<CString> businessKeySet;
	for (const auto& k : businessKeys) {
		CString low = k; low.MakeLower(); businessKeySet.insert(low);
	}

	// 使用事务包裹批量执行，减少每条 SQL 的隐式提交开销
	if (ExecuteSql("START TRANSACTION") == -1) {
		LogInfo(m_strError + _T(" | SQL: START TRANSACTION"));
		// 仍然尝试继续，但性能会受影响
	}

	// 分批构建多值 INSERT
	size_t total = rows.size();
	size_t idx = 0;
	while (idx < total) {
		size_t thisBatch = min(batchSize, total - idx);

		// 收集所有字段名的顺序（使用第一行的字段集合）
		const ParamMap& firstRow = rows[idx];
		if (firstRow.empty()) { idx += thisBatch; continue; }

		std::vector<CString> fieldsOrder;
		for (const auto& kv : firstRow) fieldsOrder.push_back(kv.first);

		CString strFields;
		for (const auto& f : fieldsOrder) {
			strFields += _T("`") + f + _T("`,");
		}
		strFields.TrimRight(_T(","));

		// 构建 VALUES 部分
		CString strValuesAll;
		for (size_t j = 0; j < thisBatch; ++j) {
			const ParamMap& row = rows[idx + j];
			CString strVals;
			for (const auto& f : fieldsOrder) {
				auto it = row.find(f);
				CString val = (it != row.end()) ? it->second : _T("");
				CString escVal = EscapeString(val);
				strVals += _T("'") + escVal + _T("',");
			}
			strVals.TrimRight(_T(","));
			strValuesAll += _T("(") + strVals + _T("),");
		}
		strValuesAll.TrimRight(_T(","));

		// 构建 UPDATE 子句：使用 fieldsOrder 中非 businessKey 字段
		CString strUpdate;
		for (const auto& f : fieldsOrder) {
			CString low = f; low.MakeLower();
			if (businessKeySet.find(low) == businessKeySet.end()) {
				strUpdate += _T("`") + f + _T("`=VALUES(`") + f + _T("`),");
			}
		}
		strUpdate.TrimRight(_T(","));

		if (strUpdate.IsEmpty()) {
			if (!businessKeys.empty()) {
				CString key = businessKeys.front();
				strUpdate.Format(_T("`%s`=`%s`"), key, key);
			} else {
				m_strError = _T("EnsureTableAndUpsertBatch Failed: No update fields and businessKeys empty.");
				LogInfo(m_strError);
				return false;
			}
		}

		CString strSql;
		strSql.Format(_T("INSERT INTO `%s` (%s) VALUES %s ON DUPLICATE KEY UPDATE %s"),
			strTableName, strFields, strValuesAll, strUpdate);

		if (ExecuteSql(CT2A(strSql)) == -1) {
			LogInfo(m_strError + _T(" | SQL: ") + strSql);
			// 出错回滚并退出
			ExecuteSql("ROLLBACK");
			return false;
		}

		idx += thisBatch;
	}

	// 提交事务
	if (ExecuteSql("COMMIT") == -1) {
		LogInfo(m_strError + _T(" | SQL: COMMIT"));
		ExecuteSql("ROLLBACK");
		return false;
	}

	return true;
}

// 创建 mes_version 表
bool CMySqlDao::CreateTableMesVersion()
{
	CString sSql = _T("CREATE TABLE `mes_version` (\n"
		"  `mysql_version` varchar(10) NOT NULL COMMENT '数据表版本',\n"
		"  `mes_version` varchar(10) NULL COMMENT 'mes版本',\n"
		"  `dll_version` varchar(10) NULL COMMENT 'MysqlDao.dll版本',\n"
		"  `create_time` datetime NOT NULL COMMENT '创建时间'\n"
		") ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;");

	if (ExecuteSql(CT2A(sSql)) == -1) {
		LogInfo(m_strError + _T(" | SQL: ") + sSql);
		return false;
	}

	return true;
}

// 检查和管理数据库版本
bool CMySqlDao::CheckAndManageVersion()
{
	// 如果已经检查过版本，则直接返回 true
	if (m_versionChecked) {
		return true;
	}

	// 标记为已检查
	m_versionChecked = true;

	// 将版本号转换为字符串便于存储
	CString strCurrentVersion;
	strCurrentVersion.Format(_T("%d"), _MES_DATA_BASE_VERSION_NUMBER_);

	// 1) 检查 mes_version 表是否存在
	CString chkSql;
	chkSql.Format(_T("SHOW TABLES LIKE 'mes_version'"));
	std::vector<std::vector<CString>> res;
	if (!QuerySql(CT2A(chkSql), res)) {
		// QuerySql 已设置 m_strError
		m_strError.Insert(0, _T("CheckAndManageVersion Failed: "));
		LogInfo(m_strError);
		return false;
	}

	// 2) 表不存在，先执行升级操作，然后创建表并插入初始记录
	if (res.empty()) {
		// 如果表不存在，视为版本 < 1，需要执行升级
		Print(Info, "Version table does not exist. Treating as version 0. Starting async upgrade...");
		
		// 创建版本表（用于记录升级状态）
		if (!CreateTableMesVersion()) {
			m_strError.Insert(0, _T("CheckAndManageVersion Failed: "));
			LogInfo(m_strError);
			return false;
		}

		// 插入"升级中"的版本记录（标记为 -1 表示升级中）
		CString insertSql;
		insertSql.Format(_T("INSERT INTO `mes_version` (mysql_version, dll_version, create_time) VALUES ('-1', '%s', NOW())"),
			_MES_MYSQL_DLL_VERSION_NUMBER_);

		if (ExecuteSql(CT2A(insertSql)) == -1) {
			m_strError.Insert(0, _T("CheckAndManageVersion Failed: "));
			LogInfo(m_strError);
			return false;
		}

		// 启动后台升级线程
		if (!m_upgradeInProgress) {
			m_upgradeInProgress = true;
			m_upgradeThread = (HANDLE)_beginthreadex(
				NULL,
				0,
				UpgradeThreadProc,
				(void*)(LPCTSTR)strCurrentVersion,
				0,
				NULL
			);
			if (m_upgradeThread == NULL) {
				m_upgradeInProgress = false;
				m_strError = _T("CheckAndManageVersion Failed: Cannot create upgrade thread.");
				LogInfo(m_strError);
				return false;
			}
		}

		Print(Info, "Upgrade thread started. Connection allowed.");
		return true;
	}

	// 3) 表存在，查询最新的 mysql_version
	CString querySql;
	querySql.Format(_T("SELECT mysql_version FROM mes_version ORDER BY create_time DESC LIMIT 1"));
	std::vector<std::vector<CString>> queryRes;
	if (!QuerySql(CT2A(querySql), queryRes)) {
		m_strError.Insert(0, _T("CheckAndManageVersion Failed: "));
		LogInfo(m_strError);
		return false;
	}

	if (queryRes.empty()) {
		// 表存在但无数据，视为版本 < 1，需要执行升级
		Print(Info, "Version table exists but has no records. Treating as version 0. Starting async upgrade...");
		
		// 插入"升级中"的版本记录（标记为 -1 表示升级中）
		CString insertSql;
		insertSql.Format(_T("INSERT INTO `mes_version` (mysql_version, dll_version, create_time) VALUES ('-1', '%s', NOW())"),
			_MES_MYSQL_DLL_VERSION_NUMBER_);

		if (ExecuteSql(CT2A(insertSql)) == -1) {
			m_strError.Insert(0, _T("CheckAndManageVersion Failed: "));
			LogInfo(m_strError);
			return false;
		}

		// 启动后台升级线程
		if (!m_upgradeInProgress) {
			m_upgradeInProgress = true;
			m_upgradeThread = (HANDLE)_beginthreadex(
				NULL,
				0,
				UpgradeThreadProc,
				(void*)(LPCTSTR)strCurrentVersion,
				0,
				NULL
			);
			if (m_upgradeThread == NULL) {
				m_upgradeInProgress = false;
				m_strError = _T("CheckAndManageVersion Failed: Cannot create upgrade thread.");
				LogInfo(m_strError);
				return false;
			}
		}

		Print(Info, "Upgrade thread started. Connection allowed.");
		return true;
	}

	// 获取表中最新的版本号
	CString dbVersion = queryRes[0][0];

	// 4) 比较版本号（字符串比较）
	int versionCmp = dbVersion.CompareNoCase(strCurrentVersion);

	if (versionCmp > 0) {
		// 数据库版本 > 代码版本，拒绝连接
		m_strError.Format(_T("CheckAndManageVersion Failed: Database version (%s) is newer than DLL version (%s). Please update the DLL."),
			dbVersion, strCurrentVersion);
		LogInfo(m_strError);
		return false;
	}
	else if (versionCmp < 0) {
		// 数据库版本 < 代码版本，需要执行升级
		// 检查是否正在升级中（版本号为-1）
		if (dbVersion.CompareNoCase(_T("-1")) == 0) {
			Print(Info, "Database upgrade is in progress. Please wait...");
			return true;  // 升级中，允许连接
		}

		Print(Info, "Database version (%s) is lower than DLL version (%s). Starting async upgrade...", (LPCTSTR)dbVersion, (LPCTSTR)strCurrentVersion);

		// 更新版本号为 -1 标记升级中
		CString updateSql;
		updateSql.Format(_T("UPDATE `mes_version` SET mysql_version = '-1', dll_version = '%s', create_time = NOW() WHERE mysql_version = '%s'"),
			_MES_MYSQL_DLL_VERSION_NUMBER_, dbVersion);

		if (ExecuteSql(CT2A(updateSql)) == -1) {
			LogInfo(_T("CheckAndManageVersion: Warning - could not update version table to mark upgrade in progress."));
		}

		// 启动后台升级线程
		if (!m_upgradeInProgress) {
			m_upgradeInProgress = true;
			m_upgradeThread = (HANDLE)_beginthreadex(
				NULL,
				0,
				UpgradeThreadProc,
				(void*)(LPCTSTR)strCurrentVersion,
				0,
				NULL
			);
			if (m_upgradeThread == NULL) {
				m_upgradeInProgress = false;
				m_strError = _T("CheckAndManageVersion Failed: Cannot create upgrade thread.");
				LogInfo(m_strError);
				return false;
			}
		}

		Print(Info, "Upgrade thread started. Connection allowed.");
		return true;
	}
	else {
		// 版本一致，无需操作
		Print(Info, "Database version (%s) matches DLL version (%s). No update needed.", (LPCTSTR)dbVersion, (LPCTSTR)strCurrentVersion);
		return true;
	}
}

// 检查表中是否存在指定的列
bool CMySqlDao::ColumnExists(const CString& tableName, const CString& columnName)
{
	if (!m_mysql) return false;

	CString sql;
	sql.Format(_T("SELECT COLUMN_NAME FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME = '%s' AND COLUMN_NAME = '%s'"),
		tableName, columnName);

	std::vector<std::vector<CString>> res;
	if (!QuerySql(CT2A(sql), res)) {
		return false;
	}

	return !res.empty();
}

// 升级到版本 1：处理 tab_err% 表的字段变更
bool CMySqlDao::UpgradeToVersion1()
{
	Print(Info, "Starting upgrade to version 1...");

	// 1) 查询所有 LIKE "tab_err%" 的表
	CString sql = _T("SHOW TABLES LIKE 'tab_err%'");
	std::vector<std::vector<CString>> tableRes;
	if (!QuerySql(CT2A(sql), tableRes)) {
		m_strError.Format(_T("UpgradeToVersion1 Failed: Cannot query tab_err tables. Error: %s"), m_strError);
		LogInfo(m_strError);
		return false;
	}

	if (tableRes.empty()) {
		Print(Info, "No tab_err%% tables found. Upgrade skipped.");
		return true;
	}

	// 2) 对每个表进行升级操作
	for (const auto& row : tableRes) {
		if (row.empty()) continue;

		CString tableName = row[0];
		Print(Info, "Upgrading table: %s", (LPCTSTR)tableName);

		// 2.1) 修改 serial_no 字段类型为 varchar(45)
		CString modifySerialNoSql;
		modifySerialNoSql.Format(_T("ALTER TABLE `%s` MODIFY COLUMN `serial_no` varchar(45) DEFAULT NULL"), tableName);

		if (ExecuteSql(CT2A(modifySerialNoSql)) == -1) {
			// 如果该字段不存在，不视为错误，继续处理
			LogInfo(_T("UpgradeToVersion1: Could not modify serial_no in ") + tableName + _T(". It may not exist."));
		} else {
			Print(Info, "Column serial_no in %s modified to varchar(45)", (LPCTSTR)tableName);
		}

		// 2.2) 检查并添加缺失的字段：recheck_result
		if (!ColumnExists(tableName, _T("recheck_result"))) {
			CString addRecheckResultSql;
			addRecheckResultSql.Format(_T("ALTER TABLE `%s` ADD COLUMN `recheck_result` tinyint(1) DEFAULT '0' COMMENT 'recheck结果'"), tableName);

			if (ExecuteSql(CT2A(addRecheckResultSql)) == -1) {
				m_strError.Format(_T("UpgradeToVersion1 Failed: Cannot add recheck_result column to %s. Error: %s"), tableName, m_strError);
				LogInfo(m_strError);
				return false;
			}
			Print(Info, "Column recheck_result added to %s", (LPCTSTR)tableName);
		} else {
			Print(Info, "Column recheck_result already exists in %s", (LPCTSTR)tableName);
		}

		// 2.3) 检查并添加缺失的字段：recheck_ImagePath
		if (!ColumnExists(tableName, _T("recheck_ImagePath"))) {
			CString addRecheckImagePathSql;
			addRecheckImagePathSql.Format(_T("ALTER TABLE `%s` ADD COLUMN `recheck_ImagePath` varchar(255) DEFAULT NULL COMMENT 'recheck图片路径'"), tableName);

			if (ExecuteSql(CT2A(addRecheckImagePathSql)) == -1) {
				m_strError.Format(_T("UpgradeToVersion1 Failed: Cannot add recheck_ImagePath column to %s. Error: %s"), tableName, m_strError);
				LogInfo(m_strError);
				return false;
			}
			Print(Info, "Column recheck_ImagePath added to %s", (LPCTSTR)tableName);
		} else {
			Print(Info, "Column recheck_ImagePath already exists in %s", (LPCTSTR)tableName);
		}
	}

	Print(Info, "Upgrade to version 1 completed successfully.");
	return true;
}

// 后台升级线程函数
unsigned int WINAPI CMySqlDao::UpgradeThreadProc(void* pParam)
{
	// 接收目标版本号
	CString strTargetVersion = (LPCTSTR)pParam;

	Print(Info, "Upgrade thread started. Target version: %s", (LPCTSTR)strTargetVersion);

	// 创建独立的CMySqlDao实例用于升级操作
	CMySqlDao* pUpgradeDao = new CMySqlDao();
	if (!pUpgradeDao) {
		Print(Error, "UpgradeThreadProc: Failed to create CMySqlDao instance.");
		m_upgradeInProgress = false;
		if (m_upgradeThread) {
			CloseHandle(m_upgradeThread);
			m_upgradeThread = NULL;
		}
		return 1;  // 错误返回
	}

	// 使用保存的连接信息连接到数据库
	if (!pUpgradeDao->Connect(
		CT2A(m_upgradeHost),
		CT2A(m_upgradeUser),
		CT2A(m_upgradePwd),
		CT2A(m_upgradeDb),
		m_upgradePort)) {
		
		Print(Error, "UpgradeThreadProc: Failed to connect to database for upgrade.");
		delete pUpgradeDao;
		m_upgradeInProgress = false;
		if (m_upgradeThread) {
			CloseHandle(m_upgradeThread);
			m_upgradeThread = NULL;
		}
		return 1;  // 错误返回
	}

	// 执行升级操作
	if (!pUpgradeDao->UpgradeToVersion1()) {
		Print(Error, "UpgradeThreadProc: Upgrade to version 1 failed.");
		delete pUpgradeDao;
		m_upgradeInProgress = false;
		if (m_upgradeThread) {
			CloseHandle(m_upgradeThread);
			m_upgradeThread = NULL;
		}
		return 1;  // 错误返回
	}

	// 升级成功后，更新版本表中的版本号从 "-1" 到目标版本号
	CString updateSql;
	updateSql.Format(_T("UPDATE `mes_version` SET mysql_version = '%s', dll_version = '%s', create_time = NOW() WHERE mysql_version = '-1'"),
		strTargetVersion, _MES_MYSQL_DLL_VERSION_NUMBER_);

	if (pUpgradeDao->ExecuteSql(CT2A(updateSql)) == -1) {
		Print(Error, "UpgradeThreadProc: Failed to update version table after upgrade.");
		delete pUpgradeDao;
		m_upgradeInProgress = false;
		if (m_upgradeThread) {
			CloseHandle(m_upgradeThread);
			m_upgradeThread = NULL;
		}
		return 1;  // 错误返回
	}

	Print(Info, "UpgradeThreadProc: Upgrade completed successfully. Version updated to %s", (LPCTSTR)strTargetVersion);

	// 清理资源
	delete pUpgradeDao;
	m_upgradeInProgress = false;
	if (m_upgradeThread) {
		CloseHandle(m_upgradeThread);
		m_upgradeThread = NULL;
	}

	return 0;  // 成功返回
}