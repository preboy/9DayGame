#pragma once

#include "LibCore/lock.h"


namespace LibNetwork
{
    // ����˵���Ϣ�ͱ�;
    struct message
    {
        USHORT	msgType;	                // ��Ϣ����;
        USHORT	msgSize;	                // ��Ϣ����;
        DWORD   msgParam;                   // socketָ��;
        char	szBuffer[PROTOCOL_BODY];	// ��Ϣ����ָ��;

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

    
    // UDPר����Ϣ����;
    struct udp_message : public message
    {
        sockaddr sockAddr;
       
        // ������dwParam��ʾ�ⲿsockaddr_in�ĵ�ַ;
        bool push( USHORT uType, CHAR* pData, USHORT uLen, DWORD dwParam )
        {
            message::push(uType, pData, uLen, dwParam);
            memcpy(&sockAddr, (DWORD*)dwParam, sizeof(sockAddr));
            dwParam = (DWORD)&sockAddr;
        }
    };


    // �ö����а�����size��T����;
	template<typename T, USHORT size = 200>	// TΪ��Ϣ�ṹ;
	class msgqueue
	{
	public:
		msgqueue(void)
		{
			m_first = m_last = 0;
		}
		~msgqueue(void)	{}
		
	public:
		// ��ʼ����Ϣ���пɴ�����Ϣ�Ĵ�С;
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

		// ѹ��һ����Ϣ��������;
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
		
		// �Ӷ����е���һ����Ϣ;
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

		// �����Ϣ�����Ƿ�Ϊ��;
		bool isEmputy()
		{
			lock_critical l( m_lock );
			return m_first == m_last;
		}

		// �����Ϣ�����Ƿ�����;
		bool isFull()
		{
			lock_critical l( m_lock );
			if ( m_first - m_last + 1 == size || m_last - m_first == 1 )
			{
				return true;
			}
			return false;
		}

		// ��ǰ��Ϣ��;
		USHORT count()
		{
			lock_critical l( m_lock );
			if ( isEmputy() )			return 0;
			if ( isFull() )				return size;
			if ( m_first > m_last )		return m_first - m_last + 1;
			if ( m_first < m_last )		return m_first - m_last + 1 + size;
		}

	private:
		// ������ʼ��ַ
		T*      m_ptrMsg[size];

		// ��m_last != m_first��ʱ��, �ӵ�m_last������m_first������, ��m_last == m_first��ʱ��, ����Ϊ��;
		// m_firstָ��һ�´δ�����ݵ�λ��, m_lastָ����һ�ζ�ȡλ��, m_last��m_first��>=0, <=size;
		USHORT	m_first, m_last;
		lock	m_lock;	// ��ֹ���߳�����;
	};

#ifdef GAME_CLIENT
    typedef msgqueue<message, 200>      message_queue;
    typedef msgqueue<udp_message, 200>  udp_message_queue;
#else
    typedef msgqueue<message, 2000>     message_queue;
    typedef msgqueue<udp_message, 2000> udp_message_queue;
#endif

}

