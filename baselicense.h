// BaseLicense.h: interface for the CBaseLicense class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BASELICENSE_H__110A91BF_FF8E_4E6F_9085_3B98501895B6__INCLUDED_)
#define AFX_BASELICENSE_H__110A91BF_FF8E_4E6F_9085_3B98501895B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FunctionModuleAgent_Time.h"
#include "LockTime.h"
#include "IReg.h"
#include "mmsystem.h"

class CBaseLicense : public CLockTime 
{
public:
	CBaseLicense()
	{
		m_bInitKey = false;
		m_bCustInfoValid = false;
		m_nTime = 0;
		m_nDay = 0;

		m_nCustID = 0;
		m_sCustName = "Unknown";
	}
	virtual ~CBaseLicense()
	{
	}

private:
	bool	m_bCustInfoValid;
	bool	m_bInitKey;
	int		m_nTime;
	int		m_nDay;

protected:
	UINT	m_nCustID;
	CString	m_sCustName;
	int		m_nTimeMax;
	int		m_nDayMax;

public:
	/////////////////////////////////////////////////////////////////////////////
	// 读写次数

	int ReadTime(IFunctionModuleInfo* pInfo)
	{
		DWORD nTime = 0xffff;
		DLL_READ_DWORD(pInfo, SP_USER_COUNTER_TIME_COUNTER, nTime);
		if( nTime != 0xffff )
		{
			WASTE_DATA1;
			m_nTime = (int)(0xfffe - nTime);
			WASTE_DATA1;
			return (int)(0xfffe - nTime);
		}
		return 0xffff;
	}

	void DecrementTime(IFunctionModuleInfo* pInfo)
	{
		DLL_DECREMENT_COUNTER(pInfo, SP_USER_COUNTER_TIME_COUNTER);
		m_nTime++;
	}

	/////////////////////////////////////////////////////////////////////////////
	// 读写天数

	int ReadDay(IFunctionModuleInfo* pInfo)
	{
		DWORD nDay = 0xffff;
		DLL_READ_DWORD(pInfo, SP_USER_COUNTER_DAY_COUNTER, nDay);
		if( nDay != 0xffff )
		{
			WASTE_DATA1;
			m_nDay = (int)(0xfffe - nDay);
			WASTE_DATA1;
			return (int)(0xfffe - nDay);
		}
		return 0xffff;
	}

	void DecrementDay(IFunctionModuleInfo* pInfo)
	{
		DLL_DECREMENT_COUNTER(pInfo, SP_USER_COUNTER_DAY_COUNTER);
		m_nDay++;
	}

	void DecrementDayWhenNeed(IFunctionModuleInfo* pInfo)
	{
		if( m_nDayMax == 0 || m_nDay >= m_nDayMax )
			return;

		// 加载上次时间
		int nDay = -1, nHour = -1, nMinute = -1;
		HKEY hKey = IReg::GetRegLoadKey( CORP_NAME + "\\License\\Time" );
		if( hKey )
		{
			IReg::RegLoadInt(hKey, "day", nDay);
			IReg::RegLoadInt(hKey, "hour", nHour);
			IReg::RegLoadInt(hKey, "minute", nMinute);
		}

		// 保存本次时间
		CTime t = CTime::GetCurrentTime();
		int nCurDay = t.GetDay(), nCurHour = t.GetHour(), nCurMinute = t.GetMinute();

		hKey = IReg::GetRegStoreKey( CORP_NAME + "\\License\\Time" );
		if( hKey )
		{
			IReg::RegStoreDWord(hKey, "day", nCurDay);
			IReg::RegStoreDWord(hKey, "hour", nCurHour);
			IReg::RegStoreDWord(hKey, "minute", nCurMinute);
		}

		// 比较时间，日期不同或者时钟后退都认为新的一天
		if( (nDay != -1 && nCurDay != nDay) || // 日期不同
			((nHour != -1 && nMinute != -1) && nCurHour * 60 + nCurMinute < nHour * 60 + nMinute) )
		{
			DecrementDay(pInfo);
		}
	}

	/////////////////////////////////////////////////////////////////////////////
	// 初始化

	bool InitSuperPro(IFunctionModuleInfo* pInfo)
	{
		if( m_bInitKey )
			return m_bCustInfoValid;
		m_bInitKey = true;


		// 软件锁：初始化
		SP_STATUS status;
		DLL_KEY_INIT(pInfo, status);
		if( status != SP_SUCCESS )
			return false;

		/*
		// 读程序TYPE
		DWORD value = 0;
		DLL_READ_DWORD(pInfo, SP_INT_APP_TYPE_INTEGER, value);
		if( !(value & GetAppType()) )
		{
			DLL_MESSAGE_BOX(pInfo, CString("Invalid App Type"));
			return false;
		}
		*/

		// 解密客户名称
		CString sName = "";
		CByteArray aCustNames;
		GetCustNameCipher( aCustNames );
		BYTE cipherBuffer[64];
		memset(cipherBuffer, 0, sizeof(cipherBuffer));
		memcpy(cipherBuffer, aCustNames.GetData(), aCustNames.GetSize());
		int nLength = aCustNames.GetSize();
		DLL_DECRYPT_TEXT(pInfo, SP_USER_AES_CUST_ID_AES, cipherBuffer, nLength, sName, status);
		if( status != SP_SUCCESS )
		{
			REPORT_KEY_STATUS(pInfo, CString("Invalid Customer"), status);
			return false;
		}
		m_sCustName = sName;

		// 读客户ID
		BYTE* signBuffer = cipherBuffer;
		PUBLIC_KEY_USER_ECC_CUST_ID;
		UINT nRetCustID;
		DLL_VERIFY_CUST(pInfo, signBuffer, nLength, SP_USER_RAW_CUST_ID_RAWDATA, m_nCustID, status, nRetCustID);

		if( status != SP_SUCCESS )
		{
			CString text;
			text.Format("Invalid Customer(%d)", nRetCustID);
			REPORT_KEY_STATUS(pInfo, text, status);
			return false;
		}
		ChangeCustName( m_nCustID, m_sCustName );

		if( m_nTimeMax != 0 )
			ReadTime(pInfo);
		if( m_nDayMax != 0 )
			ReadDay(pInfo);

		m_bCustInfoValid = true;
		return true;
	}
	//virtual WORD GetAppType() = 0;
	virtual BOOL IsNetwork() = 0;
	virtual void GetCustNameCipher(CByteArray& aCustNames) = 0;
	virtual void ChangeCustName(int nCustID, CString& sName){}

	/////////////////////////////////////////////////////////////////////////////////
	// 被次数控制的功能对象

	IFunctionModule* TimeAgentFunction(UINT nMT, CString& sID, IFunctionModule* pFunctionModule)
	{
		// 最大次数
		if( m_nTimeMax == 0 ) // 无须限制
			return NULL;
		if( IsFunctionNeedTimeAgent(nMT, sID) )
		{
			return new CFunctionModuleAgent_Time( pFunctionModule, m_nTimeMax, this );
		}
		return NULL;
	}
	virtual BOOL IsFunctionNeedTimeAgent(UINT nMT, CString& sID) = 0;

	/////////////////////////////////////////////////////////////////////////////
	// 创建功能对象

	IFunctionModule* CreateFunctionModule(UINT nMT, CString sID, UINT nCommandID, IFunctionModuleInfo* pInfo)
	{
		if( !InitSuperPro(pInfo) )
			return NULL;

		// 需要License的功能
		if( !CanLicenseFunCreate( nMT, sID ) )
			return NULL;

		IFunctionModule* pFunctionModule = DoCreateFunctionModule(sID, nCommandID);
		if( !pFunctionModule )
			return NULL;

		// 检查接口版本
		if( pFunctionModule->GetInterfaceVersion() != IFunctionModule::INTERFACE_VERSION ) // 版本发生变化
		{
			static bool bReported = false;
			if( !bReported )
			{
				AFX_MANAGE_STATE(AfxGetStaticModuleState());
				AfxMessageBox(IDS_INTERFACE_ERROR);
				bReported = true;
			}
			pFunctionModule->Release();
			return NULL;
		}

		// 次数控制(功能代理)
		IFunctionModule* pTimeAgentFunction = TimeAgentFunction( nMT, sID, pFunctionModule );
		if( pTimeAgentFunction )
			return pTimeAgentFunction;

		return pFunctionModule;
	}
	virtual BOOL CanLicenseFunCreate(UINT nMT, CString &sID) = 0;
	virtual IFunctionModule* DoCreateFunctionModule(CString& sID, UINT nCommandID) = 0;

	void GetCustInfo(CString& sCustName, int& nLicenseTime, int& nLicenseDay)
	{
		WASTE_DATA1;
		sCustName = m_sCustName;
		WASTE_DATA1;
		nLicenseTime = m_nTimeMax - m_nTime;
		WASTE_DATA1;
		nLicenseDay = m_nDayMax == 0 ? MAX_NUM : (m_nDayMax - m_nDay);
		WASTE_DATA1;
	}
};

#endif // !defined(AFX_BASELICENSE_H__110A91BF_FF8E_4E6F_9085_3B98501895B6__INCLUDED_)
