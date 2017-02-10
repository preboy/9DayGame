#pragma once
namespace LibCore
{
    const USHORT NODE_MEM_SIZE    = 32*1024;
    
    enum    // node״̬
    {
        NODE_NULL,          // ���Ի�ȡ
        NODE_FILLING,       // �������
        NODE_FILLOVER,      // ������
        NODE_USEING,        // ʹ����
    };

    struct  node
    {
        USHORT          uState;
        USHORT          uLen;
        USHORT          uSize;
        LPVOID          pBuffer;
        LPVOID          pHead;
        node*           pNext;
        
        node()
        {    
            memset( this, 0x0, sizeof(node));    
        }
        LPVOID get_nodeHead()
        {
            return pHead;
        }
        LPVOID    get_buffer()
        {
            return pBuffer;
        }
        bool init( USHORT uHeadSize, USHORT uBuffSize )
        {
            if ( nullptr == pBuffer )
            {
                pBuffer = malloc( uBuffSize );
                uSize = uBuffSize;
                memset( pBuffer, 0x0, uBuffSize );
            }
            if ( nullptr == pHead )
            {
                pHead    = malloc( uHeadSize );
                memset( pHead, 0x0, uHeadSize );
            }
            return pBuffer != nullptr;
        }

        void release()
        {
            if ( nullptr != pBuffer )
            {
                 free( pBuffer );
                 pBuffer = nullptr;
            }
            if ( nullptr != pHead )
            {
                 free( pHead );
                 pHead = nullptr;
            }
        }
    };

    // ��״����,�������߳�ʹ��
    class  list_ring
    {
    public:
        list_ring();
        ~list_ring();

        // ��ʼ��list,�趨��ʼ����ΪnNode��
        bool        init( USHORT uHeadSize, USHORT uBuffSize, USHORT uNode );
        bool        release();              // �ͷ��ڴ�
        
        USHORT      get_count();            // ��ȡ�ܹ���node��Ŀ
        USHORT      get_use_count();        // ��ȡʹ���е�node��Ŀ
        
        // ��ȡһ���յ�node�������������
        node*       get_node_for_push();
        // ��ȡһ���������ݵ�nodeָ�룬���ڴ���ҵ��
        node*       get_node_for_handle();

        int         set_node_push_completion(node* pNode);
        int         set_node_handle_completion(node* pNode);

        bool        is_emputy();    // list�Ƿ�Ϊ��
        bool        is_full();      // list�Ƿ�����

    private:
        // ��pNode��next������uNode��node,����ÿ��node�����ڴ��СΪuItems
        bool        add_nodes( node* pNode, USHORT uHeadSize, USHORT uBuffSize, USHORT uNode );

    private:
        node*       m_pHead;        // ͷָ��
        node*       m_pTail;        // β
        USHORT      m_uUse;         // nodeռ����
        USHORT      m_uNodeCount;   // node����
    };
}

