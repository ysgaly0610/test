#pragma once
#include <string>
#include "tinyxml/tinyxml.h"

class TiXmlDocument;
class TiXmlElement;

std::string UTF8_To_String(const std::string& str);

TiXmlElement * GetChildElem(TiXmlElement *pParent, const char* sTagName);

TiXmlElement * GetChildElem(TiXmlDocument *pDoc, const char* sTagName);

std::string GetTagValue(TiXmlElement *pParent, const char* sTagName );

std::string GetTagValue(TiXmlDocument *pDoc, const char* sTagName);

std::string W_To_A(const std::wstring& wstr);

std::wstring A_To_W(const std::string& str);

std::string ANSItoUTF8(const char* strAnsi);

char* utf8ToUnicode(const char* ptr);

TiXmlElement*	BuildTag(const char* sTagName, const char* sTagValue);

std::string     GetRandomStr(int nLen);
void getRowCol(int rows, int cols, int num, int& row, int& col);

void  xmlformat(CString& sXml, CString sFlag);
//获取全局唯一标识符
//CString GetGUID();