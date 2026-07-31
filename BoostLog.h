/**
@brief 日志打印模块，可以打印出时间、代码所在的文件、行数
*/
#ifndef LOG_H_
#define LOG_H_

#include <time.h>
#include <windows.h>
#include <string>

/**
@brief 一次写日志的最大长度
@note 一次性写日志的长度不能超过该值，否则程序会出错的
*/
#define LogBuff_Len 10240
//#include <boost/date_time/posix_time/posix_time.hpp>
//#include <boost/thread.hpp>

enum Level //日志等级
{
	Debug,
	Info,
	Warning,
	Error,			//虽然发生错误事件，但仍然不影响系统的继续运行
	Fatal			//可导致应用程序退出的级别
};

void LevelToStr(Level l, char *sLevel);

/**
@brief 日志类
*/
class Log
{
public:
	Log(const char* fileName, int line, int saveLog = 1, int printLog = 1, bool doCash = true);
	/**
	@brief 初始化日志类
	@param 参数与构造函数的相同
	*/
	void Init(const char* fileName, int line, int saveLog, int printLog, bool doCash);
	/**
	@brief 写日志函数，重写了()，与构造函数配合，如Log(FILENAME, __LINE__)(...)，就可以产生出带有日期、源文件、行数的日志信息
	@param 参数为变参模式，与printf函数的参数类型相同
	*/
	void operator ()(const char *charFmt, ...);

	void operator ()(Level l, const char *charFmt, ...);

	//private:
	char m_buff[LogBuff_Len];    /**<日志内容缓存>*/

	int m_saveLog;              /**<是否要把日志写入文件>*/
	int m_printLog;             /**<是否要把日子打印在屏幕上>*/
	bool m_doCash;
	//boost::posix_time::ptime nowTime;    /**<boost 的时间处理类，用于得到写日志时的时间>*/

	char m_tBuf[64]; //时间
	char m_fileNameBuf[256];//文件名
	char m_lineBuf[32];//行号
	char m_threadBuf[32];//线程号
};

/**
@brief 宏FILENAME为 写日志代码段所在的源文件名
*/
#ifdef WIN32
#define FILENAME (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#else
#define FILENAME (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif

/**
@brief 日志类构造函数的宏
*/
#define Print_Save_Nocash Log(__FILE__, __LINE__, 1, 1, false)
#define Print_Save_Docash Log(__FILE__, __LINE__, 1, 1, true)
#define NoPrint_Save_Nocash Log(__FILE__, __LINE__, 1, 0, false)
#define NoPrint_Save_Docash Log(__FILE__, __LINE__, 1, 0, true)
//#define Print Print_Save_Nocash

#ifdef LOG_NOCASH
#define Print NoPrint_Save_Nocash
#else
#define Print NoPrint_Save_Docash
#endif

/**
@brief 日志内容写硬盘缓存类，为减轻硬盘读写压力，日志在积累一定量后才写硬盘
*/
class LogManager
{
public:
	LogManager();
	~LogManager();
	/**
	@brief 把缓存里的日志内容写入文件
	*/
	void SaveLog();
	/**
	@brief 把日志类里的日志信息放入缓存，消息过长，或时间到了就写文件
	@param Log [in] 日志类
	*/
	void PutLog(const char *pBuff, int buffLen, bool doCash, Level l = Debug);
	/**
	@brief 把缓存1和缓存2里的内容连接起来写入文件
	@param pBuff [in] 缓存
	@param buffLen [in] 缓存里的内容长度
	@param pBuff2 [in] 缓存2，值为0时不考虑缓存2的数据
	@param buffLen2 [in] 缓存2里的内容长度
	*/
	void SaveFile(const char *pBuff, int buffLen, const char *pBuff2, int buffLen2, Level l = Debug);

	//************************************
	// Method:    设置当前日志等级
	// Returns:   void
	// Parameter: Level level 日志等级
	//************************************
	void SetLogLevel(Level level);
	bool m_bDebug;
	bool m_bShowCmd;
private:
	/**
	@brief 缓存长度
	*/
#define LogBuffMaxLen 20480
	/**
	@brief 缓存里的数据超出该长度的写入文件
	*/
#define LogBuffSaveLen 10240

	int m_inputLen;                 /**<缓存里的数据实际长度>*/
	char m_buff[LogBuffMaxLen];     /**<缓存>*/
	time_t m_lastSaveTime;
	CRITICAL_SECTION m_buffSection;
	//当前日志等级
	Level m_level;

	//boost::mutex m_buffMutex;        /**<缓存锁>*/
};
extern LogManager g_logManager;  /**<日志内容写硬盘缓存类 实例>*/

#if defined Name_Logon
#define LOG_FOLDER_NAME "LogonS"
#elif defined Name_GameServer
#define LOG_FOLDER_NAME "GameS"
#else
#define LOG_FOLDER_NAME "Log"
#endif
								 //#ifndef LOG_FOLDER_NAME
								 //#else
								 //#define LOG_FOLDER_NAME "log"
								 //#endif



								 /////////////////////////////////////
extern char* WcharToChar(const wchar_t* wp);
extern wchar_t* CharToWchar(const char* c);

/**
@brief 把字符数组里的信息转成16进制
@param pBuff [in] 字符数组
@param len [in] 字符数组里的内容长度
*/
extern std::string Get16Form(const char *pBuff, int len);
extern std::string Get16Form2(const char *pBuff, int len);

//把16进制的字符串转成字符串，返还0表示成功
extern int GetBuffFrom16(char *pOutBuff, int outLen, const char *pInBuff, int inLen);
/**
@brief 把字符数组里0值用'_'来代替
@param pBuff [in] 字符数组
@param len [in] 字符数组里的内容长度
*/
extern std::string GetNoNullForm(const char *pBuff, int len);


//根据sk值得到该sk的序号和使用次数
/**
@brief 得到32位整型的高16位，同时为sk的序号
*/
#define GetSKIndex(sk)	(sk>>16)
/**
@brief 得到32位整型的低16位，同时为sk的使用次数
*/
#define GetSKUsedCount(sk) (sk&0xffff)

#endif

