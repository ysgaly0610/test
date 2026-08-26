// AviLicense1.h: interface for the CAviLicense class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AVILICENSE1_H__A684A2BC_7A2B_4C7A_A859_DE4667A1BDDF__INCLUDED_)
#define AFX_AVILICENSE1_H__A684A2BC_7A2B_4C7A_A859_DE4667A1BDDF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseLicense.h"

typedef IFunctionModule* (*CREATE_FUNC)(CString, UINT);

class CAviLicense : public CBaseLicense  
{
public:
	CAviLicense();
	virtual ~CAviLicense(){}

private:
	BOOL			m_bLoadEtDll;
	CREATE_FUNC		m_pfCreate;

protected:
	//virtual WORD GetAppType();
	virtual BOOL CanLicenseFunCreate(UINT nMT, CString &sID);
	virtual BOOL IsFunctionNeedTimeAgent(UINT nMT, CString& sID);
	virtual IFunctionModule* DoCreateFunctionModule(CString& sID, UINT nCommandID);
	virtual void GetCustNameCipher(CByteArray& aCustNames);

	CREATE_FUNC GetCreateProc();

public:
	virtual BOOL IsNetwork();
};

#endif // !defined(AFX_AVILICENSE1_H__A684A2BC_7A2B_4C7A_A859_DE4667A1BDDF__INCLUDED_)
