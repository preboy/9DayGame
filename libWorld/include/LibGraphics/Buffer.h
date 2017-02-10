#pragma once

namespace LibGraphics
{
    // 顶点缓冲
    struct IVertexBuffer
    {
        enum eVertexType
        {
            eVertexType_Color,       // 颜色顶点
            eVertexType_Texture,     // 纹理顶点
        };

        virtual ~IVertexBuffer(){};

        // 释放时调用;
        virtual void            Release() = 0;
    };


    // 索引缓冲
    struct IIndexBuffer
    {
        virtual void            Release() = 0;
    };

}
