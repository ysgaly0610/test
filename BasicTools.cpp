#include "StdAfx.h"
#include "BasicTools.h"
#include "tinyxml/tinyxml.h"
#include "tinyxml/tinystr.h"
#include "BoostLog.h"


std::string UTF8_To_String(const std::string& str)
{
	int nwLen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
	wchar_t *pwBuf = new wchar_t[nwLen+1];
	memset(pwBuf, 0, nwLen*2+2);
	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), pwBuf, nwLen);
	int nLen = WideCharToMultiByte(CP_ACP, 0, pwBuf, -1, NULL, NULL, NULL, NULL);
	char* pBuf = new char[nLen+1];
	memset(pBuf, 0, nLen+1);
	WideCharToMultiByte(CP_ACP, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);
	std::string retStr = pBuf;
	delete[]pBuf;
	delete[]pwBuf;
	pBuf = NULL;
	pwBuf = NULL;
	return retStr;
}

TiXmlElement * GetChildElem(TiXmlElement *pParent, const char* sTagName)
{
	if (!pParent)
	{
		Print(Error, "pParaent is null, can not get child element %s!", sTagName);
		return NULL;
	}
	TiXmlElement *pElem = pParent->FirstChildElement();
	for ( ;pElem; pElem = pElem->NextSiblingElement())
	{
		std::string sTag = pElem->Value();
		if ( sTag == sTagName )
		{
			return pElem;
		}
	}
	return NULL;
}

TiXmlElement * GetChildElem(TiXmlDocument *pDoc, const char* sTagName)
{
	if (!pDoc)
	{
		Print(Error, "pDoc is null, can not get child element %s!", sTagName);
		return NULL;
	}
	TiXmlElement *pRoot = pDoc->RootElement();
	std::string sRootTag = pRoot->Value();
	if (sRootTag == sTagName)
	{
		return pRoot;
	}
	TiXmlElement *pElem = pRoot->FirstChildElement();
	for ( ;pElem; pElem = pElem->NextSiblingElement())
	{
		std::string sTag = pElem->Value();
		if ( sTag == sTagName )
		{
			return pElem;
		}
		else
		{
			TiXmlElement *p = GetChildElem(pElem, sTagName);
			if ( p )
				return p;
		}
	}
	Print(Error, "Child %s not exist!", sTagName);
	return NULL;
}

std::string GetTagValue(TiXmlElement *pParent, const char* sTagName)
{
	TiXmlElement *pElem = GetChildElem(pParent, sTagName);
	if ( pElem )
	{
		if ( pElem->GetText() )
			return UTF8_To_String(pElem->GetText());
	}
	return "";
}

std::string GetTagValue(TiXmlDocument *pDoc, const char* sTagName)
{
	TiXmlElement *pElem = GetChildElem(pDoc, sTagName);
	if ( pElem )
	{
		if ( pElem->GetText() )
			return UTF8_To_String(pElem->GetText());
	}
	return "";
}

std::string W_To_A(const std::wstring& wstr)
{
	Print(Info, "Convert wstring to string:");
	int nwstrlen = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, NULL, 0, NULL, NULL);
	if (nwstrlen > 0)
	{
		std::string str(nwstrlen, '\0');
		WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, (LPSTR)str.c_str(), nwstrlen, NULL, NULL);
		Print(Info, str.c_str());
		return std::move(str);
	}
	return ("");
}

std::wstring A_To_W(const std::string& str)
{
	Print(Info, "Convert string to wstring:");
	Print(Info, str.c_str());
	LPWSTR sUnicode;
	DWORD dwMinSize = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
	if ( 0 != dwMinSize )
	{
		sUnicode = new wchar_t[dwMinSize + 1];
		memset(sUnicode, 0, dwMinSize + 1);
		dwMinSize = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, sUnicode, dwMinSize);
		std::wstring sWXmlText(sUnicode, dwMinSize);
		delete [] sUnicode;
		return sWXmlText;
	}
}

std::string ANSItoUTF8(const char* strAnsi)
{
	CString sAnsi(strAnsi);
	UINT nLen = MultiByteToWideChar(936, NULL, sAnsi, -1, NULL, NULL);
	WCHAR* wszBuffer = new WCHAR[nLen + 1];
	nLen = MultiByteToWideChar(936, NULL, sAnsi, -1, wszBuffer, nLen);
	wszBuffer[nLen] = 0;
	nLen = WideCharToMultiByte(CP_UTF8, NULL, wszBuffer, -1, NULL, NULL, NULL, NULL);
	CHAR* szBuffer = new CHAR[nLen+1];
	nLen = WideCharToMultiByte(CP_UTF8, NULL, wszBuffer, -1, szBuffer, nLen, NULL, NULL );
	szBuffer[nLen] = 0;

	sAnsi = szBuffer;
	delete[] wszBuffer;
	delete[] szBuffer;
	return std::string(sAnsi.GetBuffer(0));
}

char* utf8ToUnicode(const char* ptr)
{
	int charLen = strlen(ptr); //计算pChar所指向的字符串大小，以字节为单位，一个汉字占两个字节
	int len = MultiByteToWideChar(CP_UTF8, 0, ptr, charLen, NULL, 0); //计算多字节字符的大小，按字符计算
	wchar_t * pDataBufW = new wchar_t[len + 1];
	MultiByteToWideChar(CP_UTF8, 0, ptr, charLen, pDataBufW, len); //多字节编码转换成宽字节编码
	pDataBufW[len] = '\0';
	len = WideCharToMultiByte(CP_ACP, 0, pDataBufW, (int)wcslen(pDataBufW), NULL, 0, NULL, NULL);
	char* c = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, pDataBufW, (int)wcslen(pDataBufW), c, len, NULL, NULL);
	c[len] = '\0';
	delete[] pDataBufW;
	return c;
}

TiXmlElement* BuildTag(const char* sTagName, const char* sTagValue)
{
	TiXmlElement *pTag = new TiXmlElement(sTagName);
	TiXmlText *pTagValue = new TiXmlText(sTagValue);
	pTag->LinkEndChild(pTagValue);
	return pTag;
}

std::string GetRandomStr(int nLen)
{
	static const char aAlphaNum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	std::string sTemp;
	sTemp.reserve(nLen);

	for (int i = 0; i < nLen; ++i) {
		sTemp += aAlphaNum[rand() % (sizeof(aAlphaNum) - 1)];
	}
	Print(Debug, "Get random string [%s]", sTemp.c_str());
	return sTemp;
}
//
//CString GetGUID()
//{
//	CString sGUID("error");
//
//#if !defined(NO_HTTP)
//	RPC_CSTR guidStr;
//	GUID guid;
//	HRESULT hr = CoCreateGuid(&guid);
//	if (hr == S_OK)
//	{
//		if (UuidToString(&guid, &guidStr) == RPC_S_OK)
//		{
//			sGUID = (LPTSTR)guidStr;
//			RpcStringFree(&guidStr);
//		}
//	}
//#endif
//	return sGUID;
//}

void getRowCol(int rows, int cols, int num, int& row, int& col) {
	row = (num - 1) / cols + 1;
	col = (num - 1) % cols + 1;
}

void  xmlformat(CString& sXml, CString sFlag)
{
	int nPos = sXml.Find("?xml version");
	if (nPos >= 0)
	{
		sXml = sXml.Right(sXml.GetLength() - nPos);
		sXml = "<" + sXml;
		sXml.Replace("&#xD;", "\n");
		sXml.Replace("&gt;", ">");
		sXml.Replace("&lt;", "<");
	}
	nPos = sXml.Find(sFlag);
	if (nPos >= 0)
	{
		sXml = sXml.Left(nPos);
		sXml += sFlag;
	}
}