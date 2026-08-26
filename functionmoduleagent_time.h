// FunctionModuleAgent_Time.h: interface for the CFunctionModuleAgent_Time class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FUNCTIONMODULEAGENT_TIME_H__AA1E9204_3F75_4A10_B208_84871529D8BA__INCLUDED_)
#define AFX_FUNCTIONMODULEAGENT_TIME_H__AA1E9204_3F75_4A10_B208_84871529D8BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FunctionModuleAgent.h"
#include "LockTime.h"

class CFunctionModuleAgent_Time : public CFunctionModuleAgent  
{
public:
	CFunctionModuleAgent_Time(IFunctionModule* pFunctionModule, int nMaxTime, CLockTime* pLockTime)
		:CFunctionModuleAgent(pFunctionModule)
	{
		m_nMaxTime = nMaxTime;
		m_pLockTime = pLockTime;
	}
	virtual ~CFunctionModuleAgent_Time(){}

private:
	int				m_nMaxTime;
	CLockTime*		m_pLockTime;

public:
	virtual void CFunctionModuleAgent_Time::OnCommand(IFunctionModuleInfo* pInfo )
	{
		int nTime = m_pLockTime->ReadTime(pInfo);
		if( nTime >= m_nMaxTime )
		{
			AFX_MANAGE_STATE(AfxGetStaticModuleState());
			CString text, format;
			format.LoadString(IDS_TIME_OUT);
			text.Format(format, m_nMaxTime);
			AfxMessageBox(text);
			return;
		}
		if( nTime <= m_nMaxTime )
		{
			m_pLockTime->DecrementTime(pInfo);
			CFunctionModuleAgent::OnCommand(pInfo);
		}
	}
};

#endif // !defined(AFX_FUNCTIONMODULEAGENT_TIME_H__AA1E9204_3F75_4A10_B208_84871529D8BA__INCLUDED_)
