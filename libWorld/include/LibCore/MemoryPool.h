#pragma once
/************************************************************
*
*    author:        张朝国
*    E-mail:        preboy@126.com
*    Date:        2011-02-10
*
*   内存池
************************************************************/
#pragma warning(disable:4430)

namespace LibCore
{
    // 固定大小的内存块
    template< typename T, int nType >
    class  FixMemAllocer
    {
        private:
            enum{    BLOCK_NOUSE = 0, BLOCK_USE = 1,    };
            class FixChunk;
            struct FixBlock
            {
                WORD                wState;             // 本Block是否使用 0:未使用，1 ：使用中, -1：不能使用
                WORD                wIndex;             // 处于所在Chunk中的索引
                FixBlock*           pBlockNext;         // 指向下一个块
                FixBlock();
                T*                  GetDataPtr();       // 获取本block的数据地址                                
                FixChunk*           GetChunkHead();     // 获取本block所在的chunk头
            };

            struct FixChunk
            {
                WORD                wTotalBlock;        // 总共包含的Block数
                WORD                wUseBlock;          // 使用的Block数
                DWORD               wByteSize;          // 本块内存的大小
                FixChunk*           pChunkNext;            
                FixChunk();
                FixChunk*           GetBlockHead( UINT nIndex = 0 );        // 获取第一个Block块
                void                InitChunk(    UINT nSize );             // 初始化Chunk内各个Block块
                FixChunk*           Alloc();                                // 分配一块内存
                void                Clear();
            };

    public:

        FixMemAllocer();
        ~FixMemAllocer();

        // 分配一个T大小的内存
        T*              Alloc();

        bool            Init( UINT nItemNum );
        bool            Release( T* pItem );

    private:
        // 分配一个大块 
        void            AppendChunk( UINT nSize = 64 * 1024 );
    
        // 计算指针所在的_pFirstBlock块
        FixChunk*       GetBlockPtr( T* pItem );
    
    private:
        FixChunk*       _pFirstChunk;
        WORD            _nChunkSize;
        WORD            _wItemSize;        //  每一项内存空间的大小
    };
}
