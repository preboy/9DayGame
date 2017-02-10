#pragma once
#include "LibFS/PacketFile.h"

namespace LibFS
{
    // 将一文件夹下的所有文件包括子文件夹打包成pack文件。
    class MakePacker : public CPacketFile
    {
    public:
        MakePacker();
       ~MakePacker();

       friend class CPackFolder_Header;

        // 解析文件夹并生成PAK文件;
        bool make_packer(const char* srcFolder, const char* dstFile);

        // 将PAK文件解压到目录;
        bool unpacker(const char* dstFolder);
        
    private:

        // 找一个可以使用的文件句柄;
        CRawFile* GetValidFileHandle();

        // 解析文件夹;
        bool parse_dir(const char* srcFolder);

    private:
        
        // 打包的路径; d:/a/first
        string  m_strPath;

    };
}