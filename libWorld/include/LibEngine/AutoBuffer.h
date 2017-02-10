#pragma once
#include "LibWindows/lock.h"

using namespace LibWindows;

namespace LibEngine
{
    // �Զ������С�Ļ�����;
    // ���̰߳汾;

    const UINT              nMaxBufferSize = 200*1024*1024;             // �ɷ����ڴ������С200M;

    class AutoBuffer
    {
    public:
        AutoBuffer();
        ~AutoBuffer();

        // ��ȡ��������С;
        inline UINT         GetBufferSize(){ return nSize; }

        // �����µĴ�С���ɵ����ݲ��ᶪʧ;
        bool                SetBufferSize(UINT nNewSize);

        // ��ȡ������ָ��(�Ǳ�Ҫ�������д������,����Ҫд���������ע�ⳤ�Ȳ��ɳ���nLen);
        // ��ȡ֮��Ӧ�þ����ڵ�ǰ�̵߳���ReleaseBuffer��������ܳ�������;
        // ��GetBuffer��ReleaseBuffer֮��Ĵ��룬�ɰ�ȫ�ķ������ݶ��������;
        void*               GetBuffer();

        // �ͷſ�д��Ļ�������ֻ���ڻ�ȡдָ����Ǹ��߳��е��ò���Ч;
        bool                ReleaseBuffer();

        // �������ݵ�������;
        bool                SaveData(void* pBuffer_, UINT nLen_, UINT nSize_ = 0);

        // ׷�����ݵ�������;
        bool                AddData(void* pBuffer_, UINT nLen_);

        // ���������ĩβָ�����ȵ����ݣ���nClearSizeΪ0��ʾ�����������,nClearSize���ܴ���len;
        void                ClearData(UINT nClearSize = 0);

        // ��ȡ���ݴ�С;
        inline UINT         GetDataLen(){ return nLen; }

        // ������ݼ���С;
        void                Clear();

    private:
        void                _clear();
        void                _wait();            // �ȴ�ReleaseBufferָ��;

    private:

        void*               pBuffer;            // ������ָ��;
        UINT                nSize;              // ��������С;
        UINT                nLen;               // ���ݴ�С;

        lock                theLock;            // ��ȫ��;
        DWORD               dwUsingThreadID;    // �����ݻ������������д�ķ�ʽʹ������Ϊ0������Ϊ0;   
    };
}
