#include "stdafx.h"
#include "BoostLog.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
//#include <boost/date_time/gregorian/gregorian.hpp>
//#include <boost/date_time/posix_time/posix_time.hpp>
//#include <boost/bind.hpp>

#ifdef WIN32
	#include <direct.h>
	#include <io.h>
	#include <windows.h>
#else
	#include <sys/stat.h>
	#include <time.h>
	#include <unistd.h>
#endif

static char* GetCurrPath()
{
	static char path[MAX_PATH] = {0};
	static int nCount = 1;
	if (nCount > 0)
	{
		nCount--;
		GetModuleFileName(NULL, path, MAX_PATH);
		(strrchr(path, '\\'))[0] = 0;
	}
	return path;
}
Log::Log( const char* fileName, int line, int saveLog, int printLog, bool doCash )
{
	m_saveLog = saveLog;
	m_printLog = printLog;
	m_doCash = doCash;
	if( (m_saveLog == 0 && m_printLog == 0) || (!g_logManager.m_bDebug && !g_logManager.m_bShowCmd)){
		return;
	}
	
	SYSTEMTIME tNow;
	GetLocalTime(&tNow);
	sprintf_s(m_tBuf, "[%02d:%02d:%02d.%03d]", tNow.wHour, tNow.wMinute, tNow.wSecond, tNow.wMilliseconds);
	//提取文件名
	int fileLen = (int)strlen(fileName);
	int headIndex = fileLen - 1;
	for( ; headIndex >= 0 && (fileName[headIndex] != '\\' && fileName[headIndex] != '/'); headIndex--);
	memset( m_fileNameBuf, 0, sizeof(m_fileNameBuf));
	if( fileLen - 1 - headIndex < 256 ){
		memcpy( m_fileNameBuf, fileName + headIndex + 1, fileLen - headIndex - 1 );
	}
	sprintf_s( m_lineBuf, "[%d] ", line );
	memset( m_threadBuf, 0, 32);
	sprintf_s( m_threadBuf, "[Thrd:%05d]", GetCurrentThreadId());
}

void LevelToStr(Level l, char *sLevel)
{
	std::string sTemp;
	switch(l)
	{
	case Debug:
		sTemp = " [Debug] ";
		break;
	case Info:
		sTemp = " [Info] ";
		break;
	case Warning:
		sTemp = " [Warning] ";
		break;
	case Error:
		sTemp = " [Error] ";
		break;
	case Fatal:
		sTemp = " [Fatal] ";
		break;
	}
	memcpy(sLevel, sTemp.c_str(), sTemp.length() + 1 );
}

void Log::operator()( const char *charFmt, ... )
{
	if( (m_saveLog == 0 && m_printLog == 0) || (!g_logManager.m_bDebug && !g_logManager.m_bShowCmd)){
		return;
	}
	memset( m_buff, 0, sizeof( m_buff) );
	strncpy_s( m_buff, m_tBuf, strlen(m_tBuf) );
	strncat_s( m_buff, m_threadBuf, strlen(m_threadBuf));
	strncat_s( m_buff, m_fileNameBuf, strlen( m_fileNameBuf) );
	strncat_s( m_buff, m_lineBuf, strlen(m_lineBuf));

	int curBuffLen = (int)strlen(m_buff);

	va_list ptr;
	va_start( ptr, charFmt );
	vsnprintf_s(m_buff + curBuffLen, LogBuff_Len - curBuffLen, _TRUNCATE, charFmt, ptr);
	/*_vsnprintf_s( m_buff + curBuffLen, LogBuff_Len - (curBuffLen+10), LogBuffMaxLen, charFmt, ptr );*/
	//vsnprintf( m_buff + curBuffLen, LogBuff_Len - (curBuffLen+10), charFmt, ptr );	//vs2003不行
	va_end( ptr );
	if( m_printLog ){
        printf("%s\n", m_buff);
	}
	if( m_saveLog == 0 ){
		return;
	}
	strncat_s( m_buff, "\r\n\0", strlen( "\r\n\0" ) );
	g_logManager.PutLog( m_buff, (int)strlen(m_buff), m_doCash );
}


void Log::operator()(Level l, const char *charFmt, ...)
{
	if( (m_saveLog == 0 && m_printLog == 0) || (!g_logManager.m_bDebug && !g_logManager.m_bShowCmd)){
		return;
	}

	memset( m_buff, 0, sizeof( m_buff) );
	
	strncpy_s( m_buff, m_tBuf, strlen(m_tBuf) );

	strncat_s( m_buff, m_threadBuf, strlen(m_threadBuf) );

	char levelBuf[32];
	memset(levelBuf, 0, sizeof(levelBuf));
	LevelToStr(l, levelBuf);
	strncat_s( m_buff, levelBuf, strlen( levelBuf ) );

	strncat_s( m_buff, m_fileNameBuf, strlen( m_fileNameBuf) );

	strncat_s( m_buff, m_lineBuf, strlen(m_lineBuf));

	int curBuffLen = (int)strlen(m_buff);

	va_list ptr;
	va_start( ptr, charFmt );
	vsnprintf_s(m_buff + curBuffLen,LogBuff_Len - curBuffLen, _TRUNCATE, charFmt, ptr);
	//_vsnprintf_s( m_buff + curBuffLen, LogBuff_Len - (curBuffLen+10), LogBuffMaxLen, charFmt, ptr );
	//vsnprintf( m_buff + curBuffLen, LogBuff_Len - (curBuffLen+10), charFmt, ptr );	//vs2003不行
	va_end( ptr );
	//strncat( m_buff, tmpBuff, strlen( tmpBuff ) );
	if( m_printLog ){
		printf("%s\n", m_buff);
	}
	if( m_saveLog == 0 ){
		return;
	}

	strncat_s( m_buff, "\n\0", strlen( "\n\0" ) );
	g_logManager.PutLog( m_buff, (int)strlen(m_buff), m_doCash );
}

LogManager g_logManager;
LogManager::LogManager()
{
    m_inputLen = 0;
	m_lastSaveTime = 0;
	m_bDebug = false;
	m_bShowCmd = false;

	char DebugName[512];
	sprintf_s( DebugName, "%s\\%s",GetCurrPath(),"SaveLog" );
#ifdef WIN32
	if(_access( DebugName, 0 ) >= 0 ){
		m_bDebug = true;
	}
	sprintf_s( DebugName, "SaveLog.txt" );
	if(_access( DebugName, 0 ) >= 0 ){
		m_bDebug = true;
	}
	sprintf_s( DebugName, "%s\\%s",GetCurrPath(), "ShowCmd" );
	if(_access( DebugName, 0 ) >= 0 ){
		m_bShowCmd = true;
		AllocConsole();
		//freopen("CONIN$", "r+t", stdin); 
		//freopen("CONOUT$", "w+t", stdout);
		FILE* file1, *file2;
		freopen_s(&file1, "CONIN$", "r+t", stdin);
		freopen_s(&file2, "CONOUT$", "w+t", stdout);
	}
#else
	if(access( folderName, 0 ) >= 0 ){
		m_bDebug = true;
	}
#endif
	::InitializeCriticalSection(&m_buffSection);
	//默认日志等级为debug，所有日志信息都会写入文件
	SetLogLevel(Debug);
}
LogManager::~LogManager()
{
	SaveLog();
	DeleteCriticalSection(&m_buffSection);
	if (m_bShowCmd)
		FreeConsole();
}
void LogManager::SaveLog()
{
	//boost::mutex::scoped_lock lock(m_buffMutex);
	if( m_inputLen > 0 ){
		::EnterCriticalSection( &m_buffSection );
		SaveFile(m_buff, m_inputLen, 0, 0);
		m_inputLen = 0;
		::LeaveCriticalSection( &m_buffSection );
	}
}
#define LogSaveInterval 60
void LogManager::PutLog( const char *pBuff, int inputLen, bool doCash, Level l )
{
	if (!m_bDebug) return;
	time_t curTime = time(0);
	if( doCash == false ){//不做缓存，直接写文件
		SaveFile(pBuff, inputLen, 0, 0, l);
	} else {//做缓存
		//锁一下
		::EnterCriticalSection( &m_buffSection );
		if( m_inputLen + inputLen > LogBuffSaveLen || m_lastSaveTime + LogSaveInterval < curTime ){
			//缓存满了或者时间到了，写文件
			m_lastSaveTime = curTime;
			SaveFile(m_buff, m_inputLen, pBuff, inputLen, l);
			m_inputLen = 0;
		} else {
			//否则，暂时存到缓存
			char *p = m_buff + m_inputLen;
			memcpy( p, pBuff, inputLen );
			m_inputLen += inputLen;
		}
		::LeaveCriticalSection( &m_buffSection );
	}
	//{
	//	boost::mutex::scoped_lock lock(m_buffMutex);
	//}
}
//注意，这个是要包含在线程锁 m_buffSection 里的
void LogManager::SaveFile( const char *pBuff, int buffLen, const char *pBuff2, int buffLen2, Level l)
{
	if( pBuff == 0 || l < m_level ){ //日志等级小于设定的日志等级则不写入日志文件
		return;
	}

	//boost::posix_time::ptime nowTime = boost::posix_time::second_clock::local_time();
	//boost::gregorian::date d = nowTime.date();
	//boost::posix_time::time_duration td = nowTime.time_of_day();
	//char foldName[512];
	//sprintf( foldName, "Log%s", (boost::gregorian::to_iso_extended_string( d )).data() );
	char folderName[512];
	time_t curTime = time(0);
	//struct tm* formatTime = localtime(&curTime);
	struct tm formatTime;
	localtime_s(&formatTime, &curTime);
	sprintf_s( folderName, "%s\\%s_%d-%02d-%02d", GetCurrPath(), LOG_FOLDER_NAME, formatTime.tm_year+1900, formatTime.tm_mon+1, formatTime.tm_mday );
	//文件夹不存在，先创建
#ifdef WIN32
	if(_access( folderName, 0 ) == -1 ){
		_mkdir( folderName );
	}
#else
	if(access( folderName, 0 ) == -1 ){
		mkdir( folderName, S_IWRITE );
	}
#endif
	char fileName[512];
	sprintf_s( fileName, "%s\\%02d_eap.txt" , folderName, formatTime.tm_hour );
    {
        FILE *fp;
		fopen_s(&fp, fileName, "a");
        if( fp == 0 ){
            printf("open file failed[%s]\n", fileName );
            return;
        }
        fwrite( pBuff, 1, buffLen , fp );
        if( pBuff2 ){
            fwrite( pBuff2, 1, buffLen2 , fp );
        }
        fclose( fp );
    }
}

void LogManager::SetLogLevel(Level level)
{
	m_level = level;
}

////////////////////////////////////////////////////////////////////////////

char* WcharToChar(const wchar_t* wp)
{
	char *m_char;
	int len= WideCharToMultiByte(CP_ACP,0,wp, (int)wcslen(wp),NULL,0,NULL,NULL);
	m_char=new char[len+1];
	WideCharToMultiByte(CP_ACP,0,wp, (int)wcslen(wp),m_char,len,NULL,NULL);
	m_char[len]='\0';
	return m_char;
}
wchar_t* CharToWchar(const char* c)
{
	wchar_t *m_wchar;
	int len = MultiByteToWideChar(CP_ACP,0,c, (int)strlen(c),NULL,0);
	m_wchar=new wchar_t[len+1];
	memset(m_wchar, 0, sizeof(wchar_t)*(len+1));
	MultiByteToWideChar(CP_ACP,0,c, (int)strlen(c),m_wchar,len);
	return m_wchar;
}

std::string Get16Form( const char *pBuff, int len )
{
	std::string str16;
	for( int n = 0; n < len; n ++ ){
		int i1,i2;
		char c1[2], c2[2];
		i1 = (unsigned char)pBuff[n]/16;
		i2 = (unsigned char)pBuff[n]%16;
		sprintf_s( c1, "%x", i1 );
		sprintf_s( c2, "%x", i2 );
		str16 += c1;
		str16 += c2;
	}
	return str16;
}
std::string Get16Form2( const char *pBuff, int len )
{
	std::string str16;
	for( int n = 0; n < len; n ++ ){
		if(n%16==0){
			str16 +="\r\n";
		}
		int i1,i2;
		char c1[2], c2[2];
		i1 = (unsigned char)pBuff[n]/16;
		i2 = (unsigned char)pBuff[n]%16;
		sprintf_s( c1, "%x", i1 );
		sprintf_s( c2, "%x", i2 );
		str16 += c1;
		str16 += c2;
		str16 += ' ';
	}
	return str16;
}

//把16进制的字符串转成字符串
int GetBuffFrom16( char *pOutBuff, int outLen, const char *pInBuff, int inLen)
{
	memset( pOutBuff, 0, outLen );
	if( outLen < inLen/2){
		return -1;
	}
	if( inLen % 2 != 0 ){
		return -2;
	}
	for( int n = 0; n < inLen; n += 2 ){
		//高位
		if( pInBuff[n] >= '0' && pInBuff[n] <= '9' ){
			pOutBuff[n/2] = (pInBuff[n]-'0')*16;
		} else if( pInBuff[n] >= 'a' && pInBuff[n] <= 'f' ){
			pOutBuff[n/2] = (pInBuff[n]-'a'+10)*16;
		} else if( pInBuff[n] >= 'A' && pInBuff[n] <= 'F' ){
			pOutBuff[n/2] = (pInBuff[n]-'A'+10)*16;
		} else {
			return n;
		}
		//低位
		if( pInBuff[n+1] >= '0' && pInBuff[n+1] <= '9' ){
			pOutBuff[n/2] += (pInBuff[n+1]-'0');
		} else if( pInBuff[n+1] >= 'a' && pInBuff[n+1] <= 'f' ){
			pOutBuff[n/2] += (pInBuff[n+1]-'a'+10);
		} else if( pInBuff[n+1] >= 'A' && pInBuff[n+1] <= 'F' ){
			pOutBuff[n/2] += (pInBuff[n+1]-'A'+10);
		} else {
			return n;
		}
	}
	return 0;
}

std::string GetNoNullForm( const char *pBuff, int len )
{
	std::string strnonull;
	for( int n = 0; n < len; n ++ ){
		if( pBuff[n] == 0){
			strnonull += "_";
		} else {
			strnonull += pBuff[n];
		}
	}
	return strnonull;
}

