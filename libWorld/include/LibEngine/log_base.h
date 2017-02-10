#pragma once
// #include <Windows.h>
#include "LibWindows/lock.h"

using namespace LibWindows;

#include <stdio.h>

namespace LibEngine
{
	enum 
	{
        LOG_WRITE_DEFAULT   = 0x00,
		LOG_WRITE_CONSOLE	= 0x01,
		LOG_WRITE_FILE		= 0x02,
        LOG_WRITE_DEBUG     = 0x04,
        LOG_WRITE_SERVER    = LOG_WRITE_CONSOLE | LOG_WRITE_FILE | LOG_WRITE_DEBUG,
        LOG_WRITE_CLIENT    =                     LOG_WRITE_FILE | LOG_WRITE_DEBUG,
		LOG_WRITE_ALL       = LOG_WRITE_CONSOLE | LOG_WRITE_FILE | LOG_WRITE_DEBUG,
	};

    enum
    {
        LOG_LEVEL_INFO      = 0x1,   // 基本信息;
        LOG_LEVEL_WARNING   = 0x2,   // 警告信息;
        LOG_LEVEL_ERROR     = 0x3,   // 非常严重的错误信息;
    };

	class log_base
	{
	private:
		FILE*			    m_file;
		UINT		        m_flags;
		lock			    m_lock;

	public:
		log_base(void);
		~log_base(void);

		bool		        Init( const char* szName, UINT uFlags = LOG_WRITE_DEFAULT );
		void		        Release();
		
        inline void         SetFlags( UINT uFlags ){ m_flags = uFlags; }

        // 将缓存数据刷新到文件;
		int	FlushFile();

        /*************************************************************************
         function:      WriteLog
         description:   写日志信息，若file为空则不答应file、nLine、func信息;
         argv:          [nFlags]日志的打印去处;
                        [pType] 类别如“[网络]”;
                        [nLevel]严重级别;
                        [file]  出错的文件名;
                        [nLine] 出错的文件行数;
                        [func]  出错的函数名;
        *************************************************************************/
        void WriteLog(UINT nFlags, const char* pType, UINT nLevel, const char* file, int nLine, const char* func, const char* format, ...);
	};

#define LOGI_S(...) INSTANCE(log_base)->WriteLog(LOG_WRITE_SERVER, "",  LOG_LEVEL_INFO,     __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__ );
#define LOGW_S(...) INSTANCE(log_base)->WriteLog(LOG_WRITE_SERVER, "",  LOG_LEVEL_WARNING,  __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__ );
#define LOGE_S(...) INSTANCE(log_base)->WriteLog(LOG_WRITE_SERVER, "",  LOG_LEVEL_ERROR,    __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__ );

#define LOGI_C(...) INSTANCE(log_base)->WriteLog(LOG_WRITE_CLIENT, "",  LOG_LEVEL_INFO,     __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__ );
#define LOGW_C(...) INSTANCE(log_base)->WriteLog(LOG_WRITE_CLIENT, "",  LOG_LEVEL_WARNING,  __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__ );
#define LOGE_C(...) INSTANCE(log_base)->WriteLog(LOG_WRITE_CLIENT, "",  LOG_LEVEL_ERROR,    __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__ );

}
