#pragma once

#include "Math.h"

/*
管理渲染设备;
*/

namespace LibEngine
{
    enum eRenderMode
    {
        eRenderMode_Point,              // 点
        eRenderMode_LineTrip,           // 线带
        eRenderMode_triangleTrip,       // 三角形(颜色块)
        eRenderMode_texture,            // 纹理

    };

    struct  ITexture;
    struct  IVertexBuffer;
    enum    E_WINDOW_MODE;

    class   TextPanel;
    struct  STextAttrib;

    // 不同渲染设备的基类;
    struct IRenderDevice
    {
        // 初始化及销毁
        virtual bool                Init(HWND hWnd, E_WINDOW_MODE mode) = 0;
        virtual void                Release() = 0;

        virtual void                BeginRender(float red, float green, float blue, float alpha) = 0;
        virtual void                EndRender() = 0;


        // 基本功能        
        virtual void                DrawVertex(const IVertexBuffer* pVertexBuffer, const ITexture* pTexture,
            UINT _count, UINT _index, eRenderMode _mode) = 0;


        virtual IVertexBuffer*      CreateVertexBuffer(const void* pData, UINT nByteWidth) = 0;
        virtual BOOL                UpdateVertexBuffer(const IVertexBuffer* pVertexBuffer, const void* pData, UINT nByteWidth) = 0;
        virtual void                DestroyVertexBuffer(IVertexBuffer** ppVertexBuffer) = 0;

        // 纹理;
        virtual ITexture*           CreateTextureFromFile(const WCHAR* filename) = 0;
        virtual ITexture*           CreateTextureFromMemory(const void* data, size_t _size) = 0;
        virtual ITexture*           CreateTexture(UINT w, UINT h) = 0;
        virtual void                DestroyTexture(ITexture** pTexture) = 0;
        
        virtual BOOL                RenderString(const TextPanel* pTextPanel, const char* pText, const STextAttrib* pAttrib) = 0;

    };

}
