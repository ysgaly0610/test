#pragma once

// 包含 MySQL 头文件之前必须先包含 winsock
#include <winsock.h>
#include <vector>
#include <map>
#include <set>
#include "../includeSQL/mysql.h"


// 定义简单的键值对，用于 Upsert 逻辑
typedef std::map<CString, CString> MySQLDataMap;
// 简单的键值对结构，用于Upsert构建
typedef std::map<CString, CString> ParamMap;
// 用于存储联合主键或唯一索引的字段名
typedef std::vector<CString> UniqueKeyList;

// 升级线程参数结构体
struct UpgradeThreadParam
{
	CString host;
	CString user;
	CString pwd;
	CString db;
	int port;
	CString targetVersion;
};


class CMySqlDao
{
public:
	CMySqlDao();
	virtual ~CMySqlDao();

	// --- 连接管理 ---
	bool Connect(const char* host, const char* user, const char* pwd, const char* db, int port);
	void Disconnect();
	bool IsConnected();

	// --- 通用接口 ---
	// 执行增/删/改 SQL，返回受影响行数
	int ExecuteSql(const char* lpSql);

	// 查询接口
	bool QuerySql(const char* lpSql, std::vector<std::vector<CString>>& outResults);

	// 按条件删除数据，返回受影响行数；conditionMap 为空时拒绝执行
	int DeleteByConditions(const char* strTableName, const ParamMap& conditionMap);

	// --- 核心业务：存在则更新，不存在则插入 ---
	/**
	* @param strTableName 表名
	* @param data 包含所有字段的 Map (必须包含主键或唯一索引字段)
	*/
	//bool Upsert(LPCTSTR strTableName, const MySQLDataMap& data);

	/**
	* @brief 核心功能：智能 Upsert 操作 (存在则更新，不存在则插入)
	* 利用 MySQL 的 INSERT INTO ... ON DUPLICATE KEY UPDATE 语法
	* @param strTableName 表名
	* @param dataMap 字段名和值的映射 (必须包含所有唯一键字段)
	* @param uniqueKeys 可选：构成主键或唯一索引的字段列表。
	* 如果提供，UPDATE语句将只包含非 uniqueKeys 中的字段。
	* @return 成功返回true
	*/
	bool ExecuteUpsert(const char* strTableName,
		const ParamMap& dataMap,
		const UniqueKeyList& uniqueKeys);

	// --- 辅助 ---
	CString GetLastErrorText() const { return m_strError; }

	// 获取最后一次自增的id（连接级别的）
	unsigned long long GetLastInsertId();
	unsigned long long ExecuteUpsertAndGetId(const char* strTableName,
		const ParamMap& dataMap,
		const UniqueKeyList& businessKeys);

	// 确保表存在（不存在则 Create），然后执行 Upsert（使用 businessKeys 的键和值作为唯一索引判断）
	// @param strTableName 表名
	// @param dataMap 要插入/更新的字段和值
	// @param businessKeys 用于判断唯一性的键值对（列名->值）
	bool EnsureTableAndUpsert(const char* strTableName, const ParamMap& dataMap, const UniqueKeyList& businessKeys);

	// 批量 EnsureTableAndUpsert：接受多行数据，将多条记录合并成多值 INSERT，以减少 SQL 次数
	// @param rows 要插入/更新的多行数据（每行为 ParamMap）
	bool EnsureTableAndUpsertBatch(const char* strTableName, const std::vector<ParamMap>& rows, const UniqueKeyList& businessKeys, size_t batchSize);

	// 可由用户实现的建表方法（默认不实现，返回 false）。如果你要自定义建表逻辑，请在此类中实现覆盖或修改默认实现。
	virtual bool CreateTable(const char* strTableName);


private:
	void LogInfo(LPCTSTR fmt, ...);

	// 转义字符串用于 SQL（基于 mysql_real_escape_string）
	CString EscapeString(const CString& src) const;

	// 版本控制相关的私有方法
	bool CheckAndManageVersion();
	bool CreateTableMesVersion();
	bool UpgradeToVersion1();
	bool ColumnExists(const CString& tableName, const CString& columnName);

	// 后台升级线程相关
	static unsigned int WINAPI UpgradeThreadProc(void* pParam);
	static bool m_upgradeInProgress;
	static HANDLE m_upgradeThread;
	
	// 保存当前连接信息供升级线程使用
	static CString m_upgradeHost;
	static CString m_upgradeUser;
	static CString m_upgradePwd;
	static CString m_upgradeDb;
	static int m_upgradePort;

	MYSQL* m_mysql;
	CString m_strError;
	CCriticalSection m_cs; // 线程安全
	// 缓存已确认存在的表名，减少 SHOW TABLES 调用
	std::set<CString> m_existingTablesCache;
	// 版本控制标志：记录是否已检查过版本（首次连接时检查）
	bool m_versionChecked;
	enum Table { Machine = 1, Job, Decode, TabErr, TabTest, Stack};
};


//typedef CMySqlDao* (__stdcall *CreateMysqlFunc)();
//extern "C" __declspec(dllexport) CMySqlDao* CreateMysql();
