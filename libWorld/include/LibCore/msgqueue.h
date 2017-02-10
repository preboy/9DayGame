#pragma once

#include "LibCore/lock.h"


namespace LibNetwork
{
    // 服务端的消息型别;
    struct message
    {
        USHORT	msgType;	                // 消息类型;
        USHORT	msgSize;	                // 消息长度;
        DWORD   msgParam;                   // socket指针;
        char	szBuffer[PROTOCOL_BODY];	// 消息数据指针;

        message()
        {
            msgType  = 0;
            msgSize	 = 0;
            msgParam = 0;
            memset( szBuffer, 0x0, sizeof(szBuffer) );
        }

        virtual bool push( USHORT uType, CHAR* pData, USHORT uLen, DWORD dwParam )
        {
            msgType   = uType;
            msgSize   = uLen;
            msgParam  = dwParam;
            if ( pData && uLen )
            {
                memcpy_s( szBuffer, PROTOCOL_BODY, pData, uLen );
            }
            return true;
        }

        char* get_buffer()
        {
            return szBuffer;
        }
    };

    
    // UDP专用消息类型;
    struct udp_message : public message
    {
        sockaddr sockAddr;
       
        // 在这里dwParam表示外部sockaddr_in的地址;
        bool push( USHORT uType, CHAR* pData, USHORT uLen, DWORD dwParam )
        {
            message::push(uType, pData, uLen, dwParam);
            memcpy(&sockAddr, (DWORD*)dwParam, sizeof(sockAddr));
            dwParam = (DWORD)&sockAddr;
        }
    };


    // 该队列中包含有size个T类型;
	template<typename T, USHORT size = 200>	// T为消息结构;
	class msgqueue
	{
	public:
		msgqueue(void)
		{
			m_first = m_last = 0;
		}
		~msgqueue(void)	{}
		
	public:
		// 初始化消息队列可存入消息的大小;
		void init()
		{
			lock_critical l( m_lock );
			memset( m_ptrMsg, 0, sizeof(m_ptrMsg) );
			m_first = m_last = 0;

            for( int i = 0; i < size; ++i )
            {
                m_ptrMsg[i] = new T;
            }
		}

        void release()
        {
            for( int i = 0; i < size; ++i )
            {
                delete m_ptrMsg[i];
                m_ptrMsg[i] = nullptr;
            }
        }

		// 压入一条消息到队列中;
		bool push( USHORT uType, CHAR* pData, USHORT uLen, DWORD dwParam)
		{
			lock_critical l( m_lock );

			if ( isFull() || !m_ptrMsg[m_first] )
			{
                return false;
            }

			m_ptrMsg[m_first]->push( uType, pData, uLen, dwParam );

            m_first++;
			if ( m_first >= size )
			{
                m_first = m_first - size;
            }

			return true;
		}
		
		// 从队列中弹出一条消息;
		T* pop()
		{
			lock_critical l( m_lock );

            if (isEmputy())
			{
                return nullptr;
            }

            T* pPtr = m_ptrMsg[m_last];
			
            m_last++;
            if(m_last >= size)
            {
                m_last = m_last - size;
            }

            return pPtr;
		}

		// 检测消息队列是否为空;
		bool isEmputy()
		{
			lock_critical l( m_lock );
			return m_first == m_last;
		}

		// 检测消息队列是否已满;
		bool isFull()
		{
			lock_critical l( m_lock );
			if ( m_first - m_last + 1 == size || m_last - m_first == 1 )
			{
				return true;
			}
			return false;
		}

		// 当前消息数;
		USHORT count()
		{
			lock_critical l( m_lock );
			if ( isEmputy() )			return 0;
			if ( isFull() )				return size;
			if ( m_first > m_last )		return m_first - m_last + 1;
			if ( m_first < m_last )		return m_first - m_last + 1 + size;
		}

	private:
		// 队列起始地址
		T*      m_ptrMsg[size];

		// 当m_last != m_first的时候, 从第m_last个到第m_first有数据, 当m_last == m_first的时候, 队列为空;
		// m_first指向一下次存放数据的位置, m_last指向下一次读取位置, m_last、m_first均>=0, <=size;
		USHORT	m_first, m_last;
		lock	m_lock;	// 防止多线程死锁;
	};

#ifdef GAME_CLIENT
    typedef msgqueue<message, 200>      message_queue;
    typedef msgqueue<udp_message, 200>  udp_message_queue;
#else
    typedef msgqueue<message, 2000>     message_queue;
    typedef msgqueue<udp_message, 2000> udp_message_queue;
#endif

}

