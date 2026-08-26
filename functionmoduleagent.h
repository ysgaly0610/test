// FunctionModuleAgent.h: interface for the CFunctionModuleAgent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FUNCTIONMODULEAGENT_H__AF3CDA23_F109_4E72_A045_7C94E8A823CD__INCLUDED_)
#define AFX_FUNCTIONMODULEAGENT_H__AF3CDA23_F109_4E72_A045_7C94E8A823CD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IFunctionModule.h"

class CFunctionModuleAgent : public IKmUnknownImpl<IFunctionModule>
{
public:
	CFunctionModuleAgent(IFunctionModule* pFunctionModule)
	{
		m_pFunctionModule = pFunctionModule;
	}

	virtual ~CFunctionModuleAgent()
	{
		m_pFunctionModule->Release();
	}

private:
	IFunctionModule*	m_pFunctionModule;

public:
	virtual UINT GetInterfaceVersion()
	{ return m_pFunctionModule->GetInterfaceVersion(); }

	virtual UINT GetCommandID()
	{ return m_pFunctionModule->GetCommandID(); }

	virtual void SetCommandID( UINT nID )
	{ m_pFunctionModule->SetCommandID(nID); }

	virtual bool IsEditFunction()
	{ return m_pFunctionModule->IsEditFunction(); }

	virtual void OnCommand(IFunctionModuleInfo* pInfo)
	{ m_pFunctionModule->OnCommand(pInfo); }

	virtual void OnUpdateCommand(IFunctionModuleInfo *pInfo, CCmdUI* pCmdUI)
	{ m_pFunctionModule->OnUpdateCommand(pInfo, pCmdUI); }

	virtual void OnLButtonDown( IFunctionModuleInfo* pInfo, CDC *pDC, CPoint point, bool bDbClk )
	{ m_pFunctionModule->OnLButtonDown(pInfo, pDC, point, bDbClk); }

	virtual BOOL OnRButtonDown( IFunctionModuleInfo* pInfo, CDC *pDC, CPoint point )
	{ return m_pFunctionModule->OnRButtonDown(pInfo, pDC, point); }

	virtual void OnMouseMove( IFunctionModuleInfo* pInfo, CDC* pDC, CPoint point )
	{ m_pFunctionModule->OnMouseMove(pInfo, pDC, point); }

	virtual void OnExitEdit( IFunctionModuleInfo* pInfo, CDC *pDC )
	{ m_pFunctionModule->OnExitEdit(pInfo, pDC); }

	virtual void OnDraw( IFunctionModuleInfo* pInfo, CDC* pDC )
	{ m_pFunctionModule->OnDraw(pInfo, pDC); }

	virtual BOOL OnChar( IFunctionModuleInfo* pInfo, CDC* pDC, UINT nChar )
	{ return m_pFunctionModule->OnChar(pInfo, pDC, nChar); }

	virtual BOOL IsDoing(CString& sDescription)
	{ return m_pFunctionModule->IsDoing(sDescription); }

	virtual HCURSOR GetHcursor()
	{ return m_pFunctionModule->GetHcursor(); }

	virtual BOOL GetCommandStr(CString& sDescription)
	{ return m_pFunctionModule->GetCommandStr(sDescription); }
};

#endif // !defined(AFX_FUNCTIONMODULEAGENT_H__AF3CDA23_F109_4E72_A045_7C94E8A823CD__INCLUDED_)
