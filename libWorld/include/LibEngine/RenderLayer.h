#pragma once
#include "RenderDevice.h"

#include "math.h"

namespace LibEngine
{
    class RenderLayer
    {
    public:
        RenderLayer();
       ~RenderLayer();

       // 初始化函数;
       bool             Init(HWND hWnd, E_WINDOW_MODE eWndMode);
       void             Release();


       void             BeginRender(float red, float green, float blue, float alpha);
       void             EndRender();

    

       
       // --- Core Operator-------------------;

       //IVertexBuffer*   CreateVertexBuffer(const SVertexTypeTexture* pVertexData, size_t _count);
       //IVertexBuffer*   CreateVertexBuffer(const SVertexTypeColor* pVertexData, size_t _count);

       //BOOL             UpdateVertexBuffer(const IVertexBuffer* pVertexBuffer, const SVertexTypeTexture* pVertexData, size_t _count);
       //BOOL             UpdateVertexBuffer(const IVertexBuffer* pVertexBuffer, const SVertexTypeColor* pVertexData, size_t _count);

       //void             DestroyVertexBuffer(IVertexBuffer** ppVertexBuffer);
       

       ITexture*        CreateTextureFromFile(const WCHAR* filename);
       ITexture*        CreateTextureFromMemory(const void* data, size_t _size);
       ITexture*        CreateTexture(UINT w, UINT h);
       void             DestroyTexture(ITexture** pTexture);

       // ---Base Operator-------------------;
       void             DrawLineTrip(const SVertexTypeColor* pPoints, UINT _count);
       void             DrawTriangleTrip(const SVertexTypeColor* pPoints, UINT _count);
       void             DrawPoints(const SVertexTypeColor* pPoints,  UINT _count);
       void             DrawTextureRect(int x, int y, int width, int height, const ITexture* pTexture, const skyRect& rtClip, float alpha);

       // expand operator -----------------;
       void             DrawPoint(int x, int y, D3DXCOLOR color);
       void             DrawLine(int x1, int y1, int x2, int y2, D3DXCOLOR color);
       void             DrawRect(int x, int y, int w, int h, const D3DXCOLOR& color);
       void             FillRect(int x, int y, int w, int h, const D3DXCOLOR& color);
       void             DrawTexture(int x, int y, const ITexture* pTexture, float alpha);
       void             DrawTexture(int x, int y, int width, int height, const ITexture* pTexture, float alpha);
       
       BOOL             RenderText(int x ,int y, const char* pText);       
       BOOL             RenderString(const TextPanel* pTextPanel, const char* pText, const STextAttrib* pAttrib);

       // --- aux operator ------------;
       // void             DrawText(int x, int y, const char* lpText, const skyFont& font, const D3DXCOLOR& color);

    private:
       IRenderDevice*   m_pRenderDevice;


       // 优化性功能
    private:
        IVertexBuffer*  m_pVertexBuffer;

    };
}

