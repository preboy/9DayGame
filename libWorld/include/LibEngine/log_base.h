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
        LOG_LEVEL_INFO      = 0x1,   // ������Ϣ;
        LOG_LEVEL_WARNING   = 0x2,   // ������Ϣ;
        LOG_LEVEL_ERROR     = 0x3,   // �ǳ����صĴ�����Ϣ;
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

        // ����������ˢ�µ��ļ�;
		int	FlushFile();

        /*************************************************************************
         function:      WriteLog
         description:   д��־��Ϣ����fileΪ���򲻴�Ӧfile��nLine��func��Ϣ;
         argv:          [nFlags]��־�Ĵ�ӡȥ��;
                        [pType] ����硰[����]��;
                        [nLevel]���ؼ���;
                        [file]  ������ļ���;
                        [nLine] ������ļ�����;
                        [func]  ����ĺ�����;
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
