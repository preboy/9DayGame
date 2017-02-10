#pragma once
#include "LibWindows/lock.h"

using namespace LibWindows;

namespace LibEngine
{
    // 自动管理大小的缓冲区;
    // 多线程版本;

    const UINT              nMaxBufferSize = 200*1024*1024;             // 可分配内存的最大大小200M;

    class AutoBuffer
    {
    public:
        AutoBuffer();
        ~AutoBuffer();

        // 获取缓冲区大小;
        inline UINT         GetBufferSize(){ return nSize; }

        // 设置新的大小，旧的数据不会丢失;
        bool                SetBufferSize(UINT nNewSize);

        // 获取缓冲区指针(非必要情况请勿写入数据,若非要写入的数据请注意长度不可超过nLen);
        // 获取之后应该尽快在当前线程调用ReleaseBuffer，否则可能出现死锁;
        // 在GetBuffer与ReleaseBuffer之间的代码，可安全的访问数据而不会出错;
        void*               GetBuffer();

        // 释放可写入的缓冲区，只能在获取写指针的那个线程中调用才有效;
        bool                ReleaseBuffer();

        // 拷贝数据到缓冲区;
        bool                SaveData(void* pBuffer_, UINT nLen_, UINT nSize_ = 0);

        // 追加数据到缓冲区;
        bool                AddData(void* pBuffer_, UINT nLen_);

        // 清除缓冲区末尾指定长度的数据，若nClearSize为0表示清除所有数据,nClearSize可能大于len;
        void                ClearData(UINT nClearSize = 0);

        // 获取数据大小;
        inline UINT         GetDataLen(){ return nLen; }

        // 清空数据及大小;
        void                Clear();

    private:
        void                _clear();
        void                _wait();            // 等待ReleaseBuffer指针;

    private:

        void*               pBuffer;            // 缓冲区指针;
        UINT                nSize;              // 缓冲区大小;
        UINT                nLen;               // 数据大小;

        lock                theLock;            // 安全锁;
        DWORD               dwUsingThreadID;    // 若数据缓冲区被外界以写的方式使用中则不为0，否则为0;   
    };
}
