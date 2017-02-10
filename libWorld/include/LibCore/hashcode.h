/************************************************************
*
*    author:        张朝国
*    E-mail:        preboy@126.com
*    Date:          2011-01-30
*
************************************************************/

#pragma once
#include "MemoryPool.h"

namespace LibCore
{
    inline unsigned int GetHashCode(const char *str);        // 取指定字符串的hash码

    template<typename T>
    class  HashTable
    {
    private:
        struct HashBody
        {
            T*          pPointer;
            HashBody*   pNext;
            HashBody();
        };
        struct HashNode
        {
            HashBody*    pBody;
            HashNode();
        };
        struct HashHead
        {
            DWORD        wItemNum;
            HashNode*    pNode;
            HashBody*    pList;
            HashHead();
        };

    private:
        UINT            _indexSize;
        HashHead*       _pHead;
        FixMemAllocer<HashNode, 1> _pMemAllocNode;
        FixMemAllocer<HashBody, 1> _pMemAllocBody;

    public:
        HashTable()
        {
            _pHead            = NULL;
            _indexSize        = 100;
        } 

        HashTable( UINT nTotalItem )
        {
            _pHead = NULL
            if ( nTotalItem >= 40000 )
            {
                _indexSize = 200;
            }
        }

        ~HashTable();

        bool Init()
        {
            _pHead = new HashHead[_indexSize];
        }

        bool Insert( int nKey, T* tPtr );
        T* Search( int nKey );

    };
}
