#pragma once
namespace LibCore
{
    const USHORT NODE_MEM_SIZE    = 32*1024;
    
    enum    // node状态
    {
        NODE_NULL,          // 可以获取
        NODE_FILLING,       // 填充数据
        NODE_FILLOVER,      // 填充完成
        NODE_USEING,        // 使用中
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

    // 环状链表,仅共单线程使用
    class  list_ring
    {
    public:
        list_ring();
        ~list_ring();

        // 初始化list,设定初始个数为nNode个
        bool        init( USHORT uHeadSize, USHORT uBuffSize, USHORT uNode );
        bool        release();              // 释放内存
        
        USHORT      get_count();            // 获取总共的node数目
        USHORT      get_use_count();        // 获取使用中的node数目
        
        // 获取一个空的node，用于填充数据
        node*       get_node_for_push();
        // 获取一个带有数据的node指针，用于处理业务
        node*       get_node_for_handle();

        int         set_node_push_completion(node* pNode);
        int         set_node_handle_completion(node* pNode);

        bool        is_emputy();    // list是否为空
        bool        is_full();      // list是否已满

    private:
        // 在pNode的next处增加uNode个node,其中每个node所带内存大小为uItems
        bool        add_nodes( node* pNode, USHORT uHeadSize, USHORT uBuffSize, USHORT uNode );

    private:
        node*       m_pHead;        // 头指针
        node*       m_pTail;        // 尾
        USHORT      m_uUse;         // node占用数
        USHORT      m_uNodeCount;   // node总数
    };
}

