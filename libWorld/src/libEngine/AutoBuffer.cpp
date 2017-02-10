#include "stdafx.h"
#include "LibEngine/AutoBuffer.h"

using namespace LibEngine;


AutoBuffer::AutoBuffer()
{
    nLen    = 0;
    nSize   = 0;
    pBuffer = nullptr;

    dwUsingThreadID = 0;
}

AutoBuffer::~AutoBuffer()
{
    Clear();
}

void AutoBuffer::_clear()
{
    nSize = 0;
    nLen  = 0;
    SAFE_FREE(pBuffer);
}

void AutoBuffer::Clear()
{
    lock_critical l(theLock);
    _wait();

    _clear();
}

bool AutoBuffer::SetBufferSize(UINT nNewSize)
{
    lock_critical l(theLock);
    _wait();
   
    if(nNewSize == 0 || nNewSize > nMaxBufferSize)
    {
        return false;
    }

    // 新的大小不能小于现有的数据长度;
    if(nLen && (nNewSize <= nLen))
    {
        return false;
    }

    if(nSize && (nNewSize == nSize))
    {
        return true;
    }

    void* pNewBuffer = malloc(nNewSize);
    if(!pNewBuffer)
    {
        return false;
    }

    UINT nSaveLen = nLen;
    if(nLen)
    {
        memcpy(pNewBuffer, pBuffer, nLen);
    }

    _clear();

    nLen    = nSaveLen;
    nSize   = nNewSize;
    pBuffer = pNewBuffer;

    return true;
}

bool AutoBuffer::SaveData(void* pBuffer_, UINT nLen_, UINT nSize_)
{
    lock_critical l(theLock);
    _wait();
   
    assert(pBuffer_);
    assert(nLen_);

    UINT nNewSize = nSize_;
    if(nNewSize == 0)
    {
        if(nLen_ > nMaxBufferSize)
        {
            return false;
        }
        nNewSize = nLen_;
    }

    if( nNewSize > nMaxBufferSize)
    {
        return false;
    }

    if(nNewSize != nSize)
    {
        _clear();
        pBuffer = malloc(nNewSize);
        if(!pBuffer)
        {
            return false;
        }
    }

    memcpy(pBuffer, pBuffer_, nLen_);
    nLen  = nLen_;
    nSize = nNewSize;

    return true;
}

bool AutoBuffer::AddData(void* pBuffer_, UINT nLen_)
{
    lock_critical l(theLock);
    _wait();

    // 检测空间是否足够，如果不够就分配足够的空间;
    if(nSize - nLen < nLen_)
    {
        if(!SetBufferSize(nSize + nLen_))
        {
            return false;
        }
    }

    memcpy((BYTE*)pBuffer + nLen, pBuffer_, nLen_);
    nLen += nLen_;

    return true;
}

void AutoBuffer::ClearData(UINT nClearSize)
{
    lock_critical l(theLock);
    _wait();

    if(nClearSize == 0 || nClearSize >= nLen)
    {
        nLen = 0;
    }
    else
    {
        nLen -= nLen;
    }
}

void* AutoBuffer::GetBuffer()
{
    lock_critical l(theLock);
    _wait();

    dwUsingThreadID = ::GetCurrentThreadId();

    return pBuffer;
}

bool AutoBuffer::ReleaseBuffer()
{
    if(dwUsingThreadID != ::GetCurrentThreadId())
    {
        return false;
    }

    dwUsingThreadID = 0;
  
    return true;
}

void AutoBuffer::_wait()
{
    while (dwUsingThreadID)
    {
        ::Sleep(1);
    }
}
