// EtLicenseDefine.h: interface for the CEtLicenseDefine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ETLICENSEDEFINE_H__98C74AF8_1FE7_4709_8109_0A9A57324965__INCLUDED_)
#define AFX_ETLICENSEDEFINE_H__98C74AF8_1FE7_4709_8109_0A9A57324965__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CEtLicenseDefine  
{
public:
	CEtLicenseDefine();
	virtual ~CEtLicenseDefine();

};

#define MT_BASIC		0
#define MT_NET			1	
#define MT_AVI			2

class IFunctionModule;
class IFunctionModuleInfo;

__declspec(dllexport) IFunctionModule* CreateFunctionModule(UINT nMT, CString sID, UINT nCommandID, IFunctionModuleInfo* pInfo);
__declspec(dllexport) void GetEtCustInfo(CString& sCustName, int& nLicenseTime);
__declspec(dllexport) BOOL IsKeyNetwork();

#endif // !defined(AFX_ETLICENSEDEFINE_H__98C74AF8_1FE7_4709_8109_0A9A57324965__INCLUDED_)
