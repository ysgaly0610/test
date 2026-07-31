#pragma once
#ifdef MYSQLDAO_EXPORTS
#define MYSQLDAO_API __declspec(dllexport)
#else
#define MYSQLDAO_API __declspec(dllimport)
#endif

#include <vector>
#include <map>
#include <set>
// 定义简单的键值对，用于 Upsert 逻辑
typedef std::map<CString, CString> MySQLDataMap;
// 简单的键值对结构，用于Upsert构建
typedef std::map<CString, CString> ParamMap;
// 用于存储联合主键或唯一索引的字段名
typedef std::vector<CString> UniqueKeyList;

extern "C"
{
	MYSQLDAO_API bool Connect(const char* host, const char* user, const char* pwd, const char* db, int port);
	MYSQLDAO_API void Disconnect();
	MYSQLDAO_API bool IsConnected();
	MYSQLDAO_API bool ExecuteUpsert(const char* strTableName,
		const ParamMap& dataMap,
		const UniqueKeyList& uniqueKeys);
	MYSQLDAO_API unsigned long long ExecuteUpsertAndGetId(const char* strTableName,
		const ParamMap& dataMap,
		const UniqueKeyList& businessKeys);
	MYSQLDAO_API int ExecuteSql(const char* lpSql);
	MYSQLDAO_API bool QuerySql(const char* lpSql, std::vector<std::vector<CString>>& outResults);
	MYSQLDAO_API int DeleteByConditions(const char* strTableName, const ParamMap& conditionMap);
	MYSQLDAO_API bool EnsureTableAndUpsert(const char* strTableName, const ParamMap& dataMap, const UniqueKeyList& businessKeys);
	MYSQLDAO_API bool EnsureTableAndUpsertBatch(const char* strTableName, const std::vector<ParamMap>& rows, const UniqueKeyList& businessKeys, size_t batchSize);
}