#pragma once
/************************************************************
*
*    author:        �ų���
*    E-mail:        preboy@126.com
*    Date:        2011-02-10
*
*   �ڴ��
************************************************************/
#pragma warning(disable:4430)

namespace LibCore
{
    // �̶���С���ڴ��
    template< typename T, int nType >
    class  FixMemAllocer
    {
        private:
            enum{    BLOCK_NOUSE = 0, BLOCK_USE = 1,    };
            class FixChunk;
            struct FixBlock
            {
                WORD                wState;             // ��Block�Ƿ�ʹ�� 0:δʹ�ã�1 ��ʹ����, -1������ʹ��
                WORD                wIndex;             // ��������Chunk�е�����
                FixBlock*           pBlockNext;         // ָ����һ����
                FixBlock();
                T*                  GetDataPtr();       // ��ȡ��block�����ݵ�ַ                                
                FixChunk*           GetChunkHead();     // ��ȡ��block���ڵ�chunkͷ
            };

            struct FixChunk
            {
                WORD                wTotalBlock;        // �ܹ�������Block��
                WORD                wUseBlock;          // ʹ�õ�Block��
                DWORD               wByteSize;          // �����ڴ�Ĵ�С
                FixChunk*           pChunkNext;            
                FixChunk();
                FixChunk*           GetBlockHead( UINT nIndex = 0 );        // ��ȡ��һ��Block��
                void                InitChunk(    UINT nSize );             // ��ʼ��Chunk�ڸ���Block��
                FixChunk*           Alloc();                                // ����һ���ڴ�
                void                Clear();
            };

    public:

        FixMemAllocer();
        ~FixMemAllocer();

        // ����һ��T��С���ڴ�
        T*              Alloc();

        bool            Init( UINT nItemNum );
        bool            Release( T* pItem );

    private:
        // ����һ����� 
        void            AppendChunk( UINT nSize = 64 * 1024 );
    
        // ����ָ�����ڵ�_pFirstBlock��
        FixChunk*       GetBlockPtr( T* pItem );
    
    private:
        FixChunk*       _pFirstChunk;
        WORD            _nChunkSize;
        WORD            _wItemSize;        //  ÿһ���ڴ�ռ�Ĵ�С
    };
}
