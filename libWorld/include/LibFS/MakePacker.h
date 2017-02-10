#pragma once
#include "LibFS/PacketFile.h"

namespace LibFS
{
    // ��һ�ļ����µ������ļ��������ļ��д����pack�ļ���
    class MakePacker : public CPacketFile
    {
    public:
        MakePacker();
       ~MakePacker();

       friend class CPackFolder_Header;

        // �����ļ��в�����PAK�ļ�;
        bool make_packer(const char* srcFolder, const char* dstFile);

        // ��PAK�ļ���ѹ��Ŀ¼;
        bool unpacker(const char* dstFolder);
        
    private:

        // ��һ������ʹ�õ��ļ����;
        CRawFile* GetValidFileHandle();

        // �����ļ���;
        bool parse_dir(const char* srcFolder);

    private:
        
        // �����·��; d:/a/first
        string  m_strPath;

    };
}