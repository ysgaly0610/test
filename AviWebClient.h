// AviWebClient.h : AviWebClient DLL 的主头文件
//

//#pragma once
#include "stdafx.h"
#include <vector>
//#ifndef __AFXWIN_H__
//	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
//#endif
//
//#include "resource.h"		// 主符号
//
//
//// CAviWebClientApp
//// 有关此类实现的信息，请参阅 AviWebClient.cpp
////
//using namespace std;
//class CAviWebClientApp : public CWinApp
//{
//public:
//	CAviWebClientApp();
//
//// 重写
//public:
//	virtual BOOL InitInstance();
//
//	DECLARE_MESSAGE_MAP()
//	/*
//	int callRealStatusReport(const char *server_address);
//	int callStatusChangeReport(const char *server_address);
//	int callAlarmReport(const char *server_address);
//	int callEQPInfoVerify(const char *server_address);
//	int callUserVerify(const char *server_address);
//	int callParamVerify(const char *server_address);
//	int callWIPTrackingReport(const char *server_address);
//	int callSendOutReport(const char *server_address);
//	int callJobCountReport(const char *server_address);
//	int callJobDataCreateModifyReport(const char *server_address);
//	int callRemoveRecoveryReport(const char *server_address);
//	int callUtilityReport(const char *server_address);
//	int callReciReport(const char *server_address);
//	int callEQRecipeQuery(const char *server_address);
//	int callCCDDataReport(const char *server_address);
//	int callFetchOutReport(const char *server_address);
//	int callStoreInReport(const char *server_address);
//	int callCarrierIDReport(const char *server_address);
//	int callPanelDataUploadReport(const char *server_address);
//	int callRTMReport(const char *server_address);
//	int callJobRemoveRecoveryReport(const char *server_address)
//	*/
//};

class __declspec(dllexport) AviWebClient;
class AviWebClient
{
public:
	AviWebClient(){};
	virtual ~AviWebClient(){};
	void callAllPro(int flag,const char* server_addr,const char* contents, const char* machineNo,const char* IMESPath, std::string& sResultXML = std::string() );
	int Request(const char *server_address, const std::string& sInvokeMethod, std::string& contents, std::string& sResultXML );
	void setEapPath(char* path);
	std::vector<CString> CsvSplit(CString srcCsv);
};

//std::string UTF8_To_String(const std::string& str);
