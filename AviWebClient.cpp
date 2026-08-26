// AviWebClient.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "AviWebClient.h"
#include "BasicHttpBinding_USCOREIMacIntfWS.nsmap"
#include <iostream>
#include <fstream>
#include <cstringt.h>
#include <locale.h>
#include <string>
#include <sstream> 
#include "tinyxml/tinyxml.h"
#include "soapStub.h"
#include "BoostLog.h"

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: 如果此 DLL 相对于 MFC DLL 是动态链接的，
//		则从此 DLL 导出的任何调入
//		MFC 的函数必须将 AFX_MANAGE_STATE 宏添加到
//		该函数的最前面。
//
//		例如:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 此处为普通函数体
//		}
//
//		此宏先于任何 MFC 调用
//		出现在每个函数中十分重要。这意味着
//		它必须作为函数中的第一个语句
//		出现，甚至先于所有对象变量声明，
//		这是因为它们的构造函数可能生成 MFC
//		DLL 调用。
//
//		有关其他详细信息，
//		请参阅 MFC 技术说明 33 和 58。
//

//// CAviWebClientApp
//
//BEGIN_MESSAGE_MAP(CAviWebClientApp, CWinApp)
//END_MESSAGE_MAP()
//
//
//// CAviWebClientApp 构造
CString eapPath;
//CAviWebClientApp::CAviWebClientApp()
//{
//	// TODO: 在此处添加构造代码，
//	// 将所有重要的初始化放置在 InitInstance 中
//}
//
//
//// 唯一的一个 CAviWebClientApp 对象
//
//CAviWebClientApp theApp;
//
//
//// CAviWebClientApp 初始化
//
//BOOL CAviWebClientApp::InitInstance()
//{
//	CWinApp::InitInstance();
//
//	return TRUE;
//}

void createFile(CString path,CString contents)
{
	CStdioFile file;
	file.Open(path,CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite);
	file.WriteString(contents);
	file.Close();
}

void MyCopyFile(CString SourFile,CString DstDFile)
{
	CString fromPath = SourFile + '\0';
	CString toPath = DstDFile + '\0';
	Print(Info, "原路径：%s,拷贝路径：%s",fromPath,toPath);

	//判断文件是否位空
	SHFILEOPSTRUCT fop;
	memset(&fop,0,sizeof(fop));
	fop.fFlags = FOF_NOCONFIRMATION | FOF_NOCONFIRMMKDIR | FO_RENAME | FOF_FILESONLY;
	fop.pFrom = fromPath;
	fop.pTo = toPath;
	fop.wFunc = FO_COPY;

	int nOK = SHFileOperation(&fop);
	if (nOK != 0)
	{
		Print(Error, "window错误代码：%d",nOK);
		//AfxMessageBox("文件拷贝出错!");
	}else
		DeleteFile(SourFile);
}

vector<CString> CsvSplit(CString pathName)
{
	vector<CString> rowKey;
	const char *cutFlag = ",";
	char* tempStr;
	string rowCsv;
	Print(Info, "准备解析的上传内容是：%s",pathName);
	char str[1500];

	ifstream ifile;
	ifile.open(pathName,ios::in);
	getline(ifile,rowCsv);
	getline(ifile,rowCsv);
	ifile.close();

	strcpy(str,rowCsv.c_str());
	tempStr = strtok(str,cutFlag);
	while(tempStr != NULL)
	{
		rowKey.push_back(tempStr);
		tempStr = strtok(NULL,cutFlag);
	}
	return rowKey;
}

CString dateFomat(int dateFlag)
{
	//时间格式化TRIXD
	SYSTEMTIME SystemTime;  
	::GetLocalTime(&SystemTime);  
	CString strDate1="",Date1="";  
	strDate1.Format("%04d",SystemTime.wYear);         //年
	Date1 = Date1 + strDate1;  
	strDate1.Format("%02d",SystemTime.wMonth);        //月
	Date1 = Date1 + strDate1;  
	strDate1.Format("%02d",SystemTime.wDay);          //日
	Date1 = Date1 + strDate1;  
	strDate1.Format("%02d",SystemTime.wHour);         //时
	Date1 = Date1 + strDate1; 
	strDate1.Format("%02d",SystemTime.wMinute);       //分
	Date1 = Date1 + strDate1; 
	strDate1.Format("%02d",SystemTime.wSecond);       //秒
	Date1 = Date1 + strDate1; 
	strDate1.Format("%03d",SystemTime.wMilliseconds); //毫秒 
	Date1 = Date1 + strDate1; 

	//时间格式化2 deptID
	CString strDate2="",Date2="";  
	strDate2.Format("%4d",SystemTime.wYear);  
	Date2 = Date2 + strDate2;  
	strDate2.Format("-%02d",SystemTime.wMonth);  
	Date2 = Date2 + strDate2;  
	strDate2.Format("-%02d",SystemTime.wDay);  
	Date2 = Date2 + strDate2;
	strDate2.Format("T%02d",SystemTime.wHour);  
	Date2 = Date2 + strDate2;
	strDate2.Format(":%02d",SystemTime.wMinute);  
	Date2 = Date2 + strDate2;
	strDate2.Format(":%02d",SystemTime.wSecond);  
	Date2 = Date2 + strDate2;

	//时间格式化3
	CString strDate3="",Date3="";  
	strDate3.Format("%04d",SystemTime.wYear);         //年
	Date3 = Date3 + strDate3;  
	strDate3.Format("%02d",SystemTime.wMonth);        //月
	Date3 = Date3 + strDate3;  
	strDate3.Format("%02d",SystemTime.wDay);          //日
	Date3 = Date3 + strDate3; 
	strDate1.Format("%02d",SystemTime.wHour);         //时
	Date3 = Date3 + strDate3; 
	strDate1.Format("%02d",SystemTime.wMinute);       //分
	Date3 = Date3 + strDate3; 
	strDate1.Format("%02d",SystemTime.wSecond);       //秒
	Date3 = Date3 + strDate3;
	if (dateFlag == 0)
	{
		return Date1;
	}else if(dateFlag == 1)
		return Date3;
	else
	{
		return Date2;
	}
}

CString getPanelID(CString name)
{
	CStdioFile ifile;
	CString panelID = "Test";
	if(PathFileExists(eapPath + "\\TEMPFILE\\" + name))
	{
		ifile.Open(eapPath + "\\TEMPFILE\\" + name,CFile::modeRead);
		ifile.ReadString(panelID);
		ifile.Close();
	}
	return panelID;
}

vector<CString> getUserInfo()
{
	ifstream ifile;
	vector<CString> getInfo;
	string info;
	ifile.open( eapPath + "\\TEMPFILE\\USERINFO",ios::in);
	getline(ifile,info);
	while(getline(ifile,info))
		getInfo.push_back(info.c_str());
	return getInfo;
}

char* cstrToChar(CString cstr)
{
	char* p = (LPSTR)(LPCTSTR)cstr;
	return p;
}


vector<CString> CstrSplit(CString srcCstr)
{
	vector<CString> rowKey;
	const char *cutFlag = "><";
	char* tempStr;
	char str[500];
	Print(Info, "准备解析的cstring内容是：%s",srcCstr);
	strcpy(str,srcCstr);
	tempStr = strtok(str,cutFlag);
	while(tempStr != NULL)
	{
		rowKey.push_back(tempStr);
		Print(Debug, "解析信息:%s",tempStr);
		tempStr = strtok(NULL,cutFlag);
	}
	return rowKey;
}

string dataToXml(string data)
{
	string con1 = "<?xml version=\"1.0\" encoding=\"utf-8\"?>";
	string con2 = "<Ingredients xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" WipEntity=\"" + data + "\" />";	
	return con1 + con2;// + con4;
}

static char* utf82gb2312(const char* utf8)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wstr, len);
	len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, len, NULL, NULL);
	if (wstr) delete[] wstr;
	return str;
}

//std::string UTF8_To_String(const std::string& str)
//{
//	int nwLen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
//	wchar_t *pwBuf = new wchar_t[nwLen+1];
//	memset(pwBuf, 0, nwLen*2+2);
//	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), pwBuf, nwLen);
//	int nLen = WideCharToMultiByte(CP_ACP, 0, pwBuf, -1, NULL, NULL, NULL, NULL);
//	char* pBuf = new char[nLen+1];
//	memset(pBuf, 0, nLen+1);
//	WideCharToMultiByte(CP_ACP, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);
//	std::string retStr = pBuf;
//	delete[]pBuf;
//	delete[]pwBuf;
//	pBuf = NULL;
//	pwBuf = NULL;
//	return retStr;
//}

int callAGV(const char *server_address,CString contents,CString machineNo )
{
	Print(Info, "call AGV...");	
	int iRet;
	string test;
	string test1;
	struct soap userinfoSoap;
	class _ns1__macIntf macIntf;// = new _ns1__macIntf();
	class _ns1__macIntfResponse macIntfResponse;

	soap_init(&userinfoSoap);
	soap_set_mode(&userinfoSoap, SOAP_C_UTFSTRING);

	Print(Info, "呼叫地址：%s",server_address);
	
	macIntf.methodInvoke = new std::string("CallAgv"); // Ingredients
	
	//while(0)
	{
		string con2 = "<?xml version=\"1.0\" encoding=\"utf-8\"?> <CallAgv xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" macCode=\"" + machineNo +"\" berthCode=\"In" + contents + "\" wipEntityId=''> </CallAgv>";
		macIntf.input = new std::string(con2);
		Print(Info, "呼叫AGV信息:%s\n",con2.c_str());
		//iRet = soap_call___ns5__macIntf(&userinfoSoap,server_address,NULL,&macIntf,macIntfResponse);
		iRet = soap_call___ns5__macIntf(&userinfoSoap,server_address,NULL,&macIntf,macIntfResponse);
		
		if (iRet == SOAP_OK)
		{
			int index = 0;
			int strSize = macIntfResponse.macIntfResult->_USCOREx003C_USCOREerrorCode_USCOREx003E_USCOREk_USCORE_USCOREBackingField->size();
			//for(;index < strSize;index++)
			{
				string tempValue1 = macIntfResponse.macIntfResult->_USCOREx003C_USCOREerrorCode_USCOREx003E_USCOREk_USCORE_USCOREBackingField->c_str();
				if(tempValue1 == "0")
				{
					//Print("返回值1是：%s\n",macIntfResponse.macIntfResult->_USCOREx003C_USCOREerrorCode_USCOREx003E_USCOREk_USCORE_USCOREBackingField->c_str());
					//Print("返回值2是：%s\n",macIntfResponse.macIntfResult->_USCOREx003C_USCOREerrorMsg_USCOREx003E_USCOREk_USCORE_USCOREBackingField->c_str());
					Print(Info, "返回值3是：%s\n",utf82gb2312(macIntfResponse.macIntfResult->_USCOREx003C_USCOREresultData_USCOREx003E_USCOREk_USCORE_USCOREBackingField->c_str()));
					AfxMessageBox(utf82gb2312(macIntfResponse.macIntfResult->_USCOREx003C_USCOREresultData_USCOREx003E_USCOREk_USCORE_USCOREBackingField->c_str()));
					//xmlTodata(macIntfResponse.macIntfResult->_USCOREx003C_USCOREresultData_USCOREx003E_USCOREk_USCORE_USCOREBackingField->c_str());
				}
				else
				{
					Print(Info, "AGV呼叫返回信息：%s",utf82gb2312(macIntfResponse.macIntfResult->_USCOREx003C_USCOREerrorMsg_USCOREx003E_USCOREk_USCORE_USCOREBackingField->c_str()));
					AfxMessageBox(utf82gb2312(macIntfResponse.macIntfResult->_USCOREx003C_USCOREerrorMsg_USCOREx003E_USCOREk_USCORE_USCOREBackingField->c_str()));
				}
			}
		}
		else
		{
			Print(Error, "错误代码：%d\n",iRet);
			AfxMessageBox("Error while calling the soap_out__ns1__macIntf");
			Print(Error, "Error while calling the soap_out__ns1__macIntf\n");
		}
	}
	
	delete(macIntf.methodInvoke);
	delete(macIntf.input);
	soap_destroy(&userinfoSoap);   
	soap_end(&userinfoSoap);   
	soap_done(&userinfoSoap);
	return iRet;
	
}

vector<CString> getDecoFileName(CString path)
{
	vector<CString> decodes;
	const char *to_search = path;					//欲查找的文件，支持通配符
	long handle;                                    //用于查找的句柄
	CString fileName = "nothing";
	struct _finddata_t fileinfo;                    //文件信息的结构体
	handle = _findfirst(to_search,&fileinfo);	    //第一次查找
	if(-1 == handle)
		return decodes;
	fileName = fileinfo.name;
	decodes.push_back(fileName);
	//printf("%s\n",fileinfo.name);                 //打印出找到的文件的文件名
	while(!_findnext(handle,&fileinfo))             //循环查找其他符合的文件，直到找不到其他的为止
	{
		//printf("%s\n",fileinfo.name);
		fileName = fileinfo.name;
		decodes.push_back(fileName);
	}
	_findclose(handle);                             //关闭句柄
	return decodes;
}

vector<CString> getTxtStr(CString pathName);

int DataUpload(const char *server_address,CString contents,CString machineNo )
{
	Print(Info, "Data upload...");
	int iRet;
	string test;
	string test1;
	struct soap userinfoSoap;
	class _ns1__macIntf macIntf;// = new _ns1__macIntf();
	class _ns1__macIntfResponse macIntfResponse;

	soap_init(&userinfoSoap);
	soap_set_mode(&userinfoSoap, SOAP_C_UTFSTRING);

	Print(Info, "呼叫地址：%s",server_address);

	//macIntf.methodInvoke = new std::string("Ingredients"); // Ingredients
	macIntf.methodInvoke = new std::string("DataUpload");

	//while(0)
	{
		//string con2 = "<?xml version=\"1.0\" encoding=\"utf-8\"?>< Ingredients xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" macCode=\"AC210444\" wipEntity=\"13975891\"> </ Ingredients >";
		string con2 = contents.GetBuffer(0);
		macIntf.input = new std::string(con2);
		Print(Info, "数据上传信息:%s\n",con2.c_str());
		//iRet = soap_call___ns5__macIntf(&userinfoSoap,server_address,NULL,&macIntf,macIntfResponse);
		iRet = soap_call___ns5__macIntf(&userinfoSoap,server_address,NULL,&macIntf,macIntfResponse);

		if (iRet == SOAP_OK)
		{
			int index = 0;
			int strSize = macIntfResponse.macIntfResult->_USCOREx003C_USCOREerrorCode_USCOREx003E_USCOREk_USCORE_USCOREBackingField->size();
			//for(;index < strSize;index++)
			{
				string tempValue1 = macIntfResponse.macIntfResult->_USCOREx003C_USCOREerrorCode_USCOREx003E_USCOREk_USCORE_USCOREBackingField->c_str();
				if(tempValue1 == "0")
				{
					//Print("返回值1是：%s\n",macIntfResponse.macIntfResult->_USCOREx003C_USCOREerrorCode_USCOREx003E_USCOREk_USCORE_USCOREBackingField->c_str());
					//Print("返回值2是：%s\n",macIntfResponse.macIntfResult->_USCOREx003C_USCOREerrorMsg_USCOREx003E_USCOREk_USCORE_USCOREBackingField->c_str());
					Print(Info, "返回值3是：%s\n",utf82gb2312(macIntfResponse.macIntfResult->_USCOREx003C_USCOREresultData_USCOREx003E_USCOREk_USCORE_USCOREBackingField->c_str()));
					AfxMessageBox(utf82gb2312(macIntfResponse.macIntfResult->_USCOREx003C_USCOREresultData_USCOREx003E_USCOREk_USCORE_USCOREBackingField->c_str()));
					//xmlTodata(macIntfResponse.macIntfResult->_USCOREx003C_USCOREresultData_USCOREx003E_USCOREk_USCORE_USCOREBackingField->c_str());
				}
				else
				{
					Print(Info, "返回信息：%s",utf82gb2312(macIntfResponse.macIntfResult->_USCOREx003C_USCOREerrorMsg_USCOREx003E_USCOREk_USCORE_USCOREBackingField->c_str()));
					AfxMessageBox(utf82gb2312(macIntfResponse.macIntfResult->_USCOREx003C_USCOREerrorMsg_USCOREx003E_USCOREk_USCORE_USCOREBackingField->c_str()));
				}
			}
		}
		else
		{
			Print(Error, "错误代码：%d\n",iRet);
			AfxMessageBox("Mes UploadData failed!");
			Print(Error, "Mes UploadData failed!iRet:%d\n", iRet);
		}
	}

	delete(macIntf.methodInvoke);
	delete(macIntf.input);
	soap_destroy(&userinfoSoap);   
	soap_end(&userinfoSoap);   
	soap_done(&userinfoSoap);
	return iRet;
}

int AlarmUpload(const char *server_address,CString contents,CString machineNo)
{
	Print(Info, "Alarm upload...");
	int iRet;
	string test;
	string test1;
	struct soap userinfoSoap;
	class _ns1__macIntf macIntf;// = new _ns1__macIntf();
	class _ns1__macIntfResponse macIntfResponse;

	soap_init(&userinfoSoap);
	soap_set_mode(&userinfoSoap, SOAP_C_UTFSTRING);

	Print(Info, "呼叫地址：%s",server_address);

	//macIntf.methodInvoke = new std::string("Ingredients"); // Ingredients
	macIntf.methodInvoke = new std::string("AlarmUpload");

	//while(0)
	{
		//string con2 = "<?xml version=\"1.0\" encoding=\"utf-8\"?>< Ingredients xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" macCode=\"AC210444\" wipEntity=\"13975891\"> </ Ingredients >";
		string con2 = contents.GetBuffer(0);
		macIntf.input = new std::string(con2);
		Print(Info, "报警信息:%s\n",con2.c_str());
		//iRet = soap_call___ns5__macIntf(&userinfoSoap,server_address,NULL,&macIntf,macIntfResponse);
		iRet = soap_call___ns5__macIntf(&userinfoSoap,server_address,NULL,&macIntf,macIntfResponse);

		if (iRet == SOAP_OK)
		{
			int index = 0;
			int strSize = macIntfResponse.macIntfResult->_USCOREx003C_USCOREerrorCode_USCOREx003E_USCOREk_USCORE_USCOREBackingField->size();
			//for(;index < strSize;index++)
			{
				string tempValue1 = macIntfResponse.macIntfResult->_USCOREx003C_USCOREerrorCode_USCOREx003E_USCOREk_USCORE_USCOREBackingField->c_str();
				if(tempValue1 == "0")
				{
					//Print("返回值1是：%s\n",macIntfResponse.macIntfResult->_USCOREx003C_USCOREerrorCode_USCOREx003E_USCOREk_USCORE_USCOREBackingField->c_str());
					//Print("返回值2是：%s\n",macIntfResponse.macIntfResult->_USCOREx003C_USCOREerrorMsg_USCOREx003E_USCOREk_USCORE_USCOREBackingField->c_str());
					Print(Info, "返回值3是：%s\n",utf82gb2312(macIntfResponse.macIntfResult->_USCOREx003C_USCOREresultData_USCOREx003E_USCOREk_USCORE_USCOREBackingField->c_str()));
					AfxMessageBox(utf82gb2312(macIntfResponse.macIntfResult->_USCOREx003C_USCOREresultData_USCOREx003E_USCOREk_USCORE_USCOREBackingField->c_str()));
					//xmlTodata(macIntfResponse.macIntfResult->_USCOREx003C_USCOREresultData_USCOREx003E_USCOREk_USCORE_USCOREBackingField->c_str());
				}
				else
				{
					Print(Info, "返回信息：%s",utf82gb2312(macIntfResponse.macIntfResult->_USCOREx003C_USCOREerrorMsg_USCOREx003E_USCOREk_USCORE_USCOREBackingField->c_str()));
					AfxMessageBox(utf82gb2312(macIntfResponse.macIntfResult->_USCOREx003C_USCOREerrorMsg_USCOREx003E_USCOREk_USCORE_USCOREBackingField->c_str()));
				}
			}
		}
		else
		{
			Print(Error, "错误代码：%d\n",iRet);
			AfxMessageBox("Mes AlarmUpload failed!");
			Print(Error, "Mes AlarmUpload failed, iRet:%d\n", iRet);
		}
	}

	delete(macIntf.methodInvoke);
	delete(macIntf.input);
	soap_destroy(&userinfoSoap);   
	soap_end(&userinfoSoap);   
	soap_done(&userinfoSoap);
	return iRet;
}

int Ingredients(const char *server_address,CString contents,CString machineNo, std::string& sResultXML )
{
	Print(Info, "Ingredients...");
	int iRet;
	string test;
	string test1;
	struct soap userinfoSoap;
	class _ns1__macIntf macIntf;// = new _ns1__macIntf();
	class _ns1__macIntfResponse macIntfResponse;

	soap_init(&userinfoSoap);
	soap_set_mode(&userinfoSoap, SOAP_C_UTFSTRING);

	Print(Info, "呼叫地址：%s",server_address);

	macIntf.methodInvoke = new std::string("Ingredients"); // Ingredients

	//while(0)
	{
		//string con2 = "<?xml version=\"1.0\" encoding=\"utf-8\"?>< Ingredients xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" macCode=\"AC210444\" wipEntity=\"13975891\"> </ Ingredients >";
		//string con2 = "<?xml version=\"1.0\" encoding=\"utf-8\"?>< Ingredients xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\"" + contents  + "> </ Ingredients >";
		string con2 = contents.GetBuffer(0);
		macIntf.input = new std::string(con2);
		Print(Info, "配方信息:%s\n",con2.c_str());
		//iRet = soap_call___ns5__macIntf(&userinfoSoap,server_address,NULL,&macIntf,macIntfResponse);
		iRet = soap_call___ns5__macIntf(&userinfoSoap,server_address,NULL,&macIntf,macIntfResponse); //这个函数是阻塞的吗？

		if (iRet == SOAP_OK)
		{
			int index = 0;
			int strSize = macIntfResponse.macIntfResult->_USCOREx003C_USCOREerrorCode_USCOREx003E_USCOREk_USCORE_USCOREBackingField->size();
			//for(;index < strSize;index++)
			{
				string tempValue1 = macIntfResponse.macIntfResult->_USCOREx003C_USCOREerrorCode_USCOREx003E_USCOREk_USCORE_USCOREBackingField->c_str();
				if(tempValue1 == "0")
				{
					//Print("返回值1是：%s\n",macIntfResponse.macIntfResult->_USCOREx003C_USCOREerrorCode_USCOREx003E_USCOREk_USCORE_USCOREBackingField->c_str());
					//Print("返回值2是：%s\n",macIntfResponse.macIntfResult->_USCOREx003C_USCOREerrorMsg_USCOREx003E_USCOREk_USCORE_USCOREBackingField->c_str());
					
					Print(Info, "返回值3是：%s\n",utf82gb2312(macIntfResponse.macIntfResult->_USCOREx003C_USCOREresultData_USCOREx003E_USCOREk_USCORE_USCOREBackingField->c_str()));
					//AfxMessageBox(utf82gb2312(macIntfResponse.macIntfResult->_USCOREx003C_USCOREresultData_USCOREx003E_USCOREk_USCORE_USCOREBackingField->c_str()));
					//xmlTodata(macIntfResponse.macIntfResult->_USCOREx003C_USCOREresultData_USCOREx003E_USCOREk_USCORE_USCOREBackingField->c_str());
					//sResultXML = utf82gb2312(macIntfResponse.macIntfResult->_USCOREx003C_USCOREresultData_USCOREx003E_USCOREk_USCORE_USCOREBackingField->c_str());
					sResultXML = macIntfResponse.macIntfResult->_USCOREx003C_USCOREresultData_USCOREx003E_USCOREk_USCORE_USCOREBackingField->c_str();
					while ( sResultXML.front() != '<')
					{
						Print(Warning, "The returned string is not standard ingredient xml, remove first charactor!");
						sResultXML.erase(0, 1);
					}
				}
				else
				{
					Print(Info, "配方返回信息：%s",utf82gb2312(macIntfResponse.macIntfResult->_USCOREx003C_USCOREerrorMsg_USCOREx003E_USCOREk_USCORE_USCOREBackingField->c_str()));
					AfxMessageBox(utf82gb2312(macIntfResponse.macIntfResult->_USCOREx003C_USCOREerrorMsg_USCOREx003E_USCOREk_USCORE_USCOREBackingField->c_str()));
				}
			}
		}
		else
		{
			Print(Error, "错误代码：%d\n",iRet);
			AfxMessageBox("Mes ingredient request failed!");
			Print(Error, "Mes inigredient request failed, iRet:%d\n", iRet);
		}
	}

	delete(macIntf.methodInvoke);
	delete(macIntf.input);
	soap_destroy(&userinfoSoap);   
	soap_end(&userinfoSoap);   
	soap_done(&userinfoSoap);
	return iRet;
}

int AviWebClient::Request(const char *server_address, const std::string& sInvokeMethod, std::string& contents, std::string& sResultXML )
{
	Print(Info, "Request to mes...");
	sResultXML.clear();
	int iRet;
	string test;
	string test1;
	struct soap userinfoSoap;
	class _ns1__macIntf macIntf;// = new _ns1__macIntf();
	class _ns1__macIntfResponse macIntfResponse;

	soap_init(&userinfoSoap);
	soap_set_mode(&userinfoSoap, SOAP_C_UTFSTRING);

	Print(Info, "呼叫地址：%s",server_address);

	macIntf.methodInvoke = new std::string(sInvokeMethod); // xml 方法头

	string con2 = contents;
	macIntf.input = new std::string(con2);
	Print(Info, "请求信息:%s\n",con2.c_str());
	iRet = soap_call___ns5__macIntf(&userinfoSoap,server_address,NULL,&macIntf,macIntfResponse); //这个函数是阻塞的吗？
	if (iRet == SOAP_OK)
	{
		int index = 0;
		int strSize = macIntfResponse.macIntfResult->_USCOREx003C_USCOREerrorCode_USCOREx003E_USCOREk_USCORE_USCOREBackingField->size();
		string tempValue1 = macIntfResponse.macIntfResult->_USCOREx003C_USCOREerrorCode_USCOREx003E_USCOREk_USCORE_USCOREBackingField->c_str();
		if(tempValue1 == "0")
		{
			Print(Info, "返回值3是：%s\n",utf82gb2312(macIntfResponse.macIntfResult->_USCOREx003C_USCOREresultData_USCOREx003E_USCOREk_USCORE_USCOREBackingField->c_str()));
			AfxMessageBox(utf82gb2312(macIntfResponse.macIntfResult->_USCOREx003C_USCOREresultData_USCOREx003E_USCOREk_USCORE_USCOREBackingField->c_str()));
			sResultXML = utf82gb2312(macIntfResponse.macIntfResult->_USCOREx003C_USCOREresultData_USCOREx003E_USCOREk_USCORE_USCOREBackingField->c_str());
		}
		else
		{
			Print(Info, "返回信息：%s",utf82gb2312(macIntfResponse.macIntfResult->_USCOREx003C_USCOREerrorMsg_USCOREx003E_USCOREk_USCORE_USCOREBackingField->c_str()));
			AfxMessageBox(utf82gb2312(macIntfResponse.macIntfResult->_USCOREx003C_USCOREerrorMsg_USCOREx003E_USCOREk_USCORE_USCOREBackingField->c_str()));
		}	
	}
	else
	{
		Print(Error, "错误代码：%d\n",iRet);
		AfxMessageBox("Request to mes failed!");
		Print(Error, "Request to mes failed!,iRet:%d\n", iRet);
	}

	delete(macIntf.methodInvoke);
	delete(macIntf.input);
	soap_destroy(&userinfoSoap);   
	soap_end(&userinfoSoap);   
	soap_done(&userinfoSoap);
	return iRet;
}

void AviWebClient::callAllPro(int flag,const char* server_addr,const char* contents, const char* machineNo, const char* IMESPath, std::string& sResultXML )
{
	Print(Info, "调用上传函数接口:flag[%d]addr[%s]content[%s]machi[%s]",flag,server_addr,contents,machineNo);
	//CString path = IMESPath;
	int iRet;
	switch (flag){
	case 1:
		iRet = callAGV(server_addr,contents,machineNo);  //南通深南N12 - 呼叫AGV
		break;
	case 2:
		iRet = DataUpload(server_addr,contents,machineNo);  // 坪地深南2厂AVI - 加工参数上传
		break;
	case 3:
		iRet = AlarmUpload(server_addr,contents,machineNo);   //坪地深南2厂AVI - 报警上传
		break;
	case 4:
		iRet = Ingredients(server_addr,contents,machineNo, sResultXML);   //坪地深南2厂AVI - 扫码调配方
		break;
	}
}

void AviWebClient::setEapPath(char* path)
{
	eapPath = path;
}

vector<CString> getTxtStr(CString pathName)
{
	vector<CString> contens;
	CString tempStr;
	CStdioFile cfile;
	if(PathFileExists(pathName))
	{
		cfile.Open(pathName,CFile::modeRead);
		while(cfile.ReadString(tempStr))
			contens.push_back(tempStr);
	}
	return contens;
}