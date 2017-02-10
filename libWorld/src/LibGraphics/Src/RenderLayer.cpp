#include "stdafx.h"
#include "LibGraphics/RenderLayer.h"

#include "LibGraphics/WinGameApp.h"
#include "LibGraphics/Texture.h"
#include "DX11/RenderDevice_DX11.h"

#include "LibGraphics/TextureFont.h"

namespace LibGraphics
{

    RenderLayer::RenderLayer()
    {
        m_pRenderDevice = nullptr;
        m_pVertexBuffer = nullptr;
    }

    RenderLayer::~RenderLayer()
    {
    }

    void RenderLayer::BeginRender(float red, float green, float blue, float alpha)
    {
        if(m_pRenderDevice)
        {
            m_pRenderDevice->BeginRender(red, green, blue, alpha);
        }
    }

    void RenderLayer::EndRender()
    {
        if(m_pRenderDevice)
        {
            m_pRenderDevice->EndRender();
        }
    }

    bool RenderLayer::Init(HWND hWnd, E_WINDOW_MODE eWndMode)
    {
        m_pRenderDevice = new RenderDevice_DX11;
        if(!m_pRenderDevice || !m_pRenderDevice->Init(hWnd, eWndMode))
        {
            return false;
        }

        SVertexTypeTexture vertices[4];
        m_pVertexBuffer = m_pRenderDevice->CreateVertexBuffer(vertices, 4 * sizeof(SVertexTypeTexture));

        return true;
    }

    void RenderLayer::Release()
    {
        m_pRenderDevice->DestroyVertexBuffer(&m_pVertexBuffer);

        if(m_pRenderDevice)
        {
            m_pRenderDevice->Release();
            RenderDevice_DX11* pRenderDeviceDx11 = (RenderDevice_DX11*)m_pRenderDevice;
            delete pRenderDeviceDx11;
            m_pRenderDevice = nullptr;
        }
    }


    //IVertexBuffer* RenderLayer::CreateVertexBuffer(const SVertexTypeTexture* pVertexData, size_t _count)
    //{
    //    if(m_pRenderDevice)
    //    {
    //        return m_pRenderDevice->CreateVertexBuffer(pVertexData, sizeof(SVertexTypeTexture)*_count);
    //    }

    //    return nullptr;
    //}

    //IVertexBuffer* RenderLayer::CreateVertexBuffer(const SVertexTypeColor* pVertexData, size_t _count)
    //{
    //    if(m_pRenderDevice)
    //    {
    //        return m_pRenderDevice->CreateVertexBuffer(pVertexData, sizeof(SVertexTypeColor)*_count);
    //    }

    //    return nullptr;
    //}
    //

    //BOOL RenderLayer::UpdateVertexBuffer(const IVertexBuffer* pVertexBuffer, const SVertexTypeColor* pVertexData, size_t _count)
    //{
    //    if(m_pRenderDevice)
    //    {
    //        return m_pRenderDevice->UpdateVertexBuffer(pVertexBuffer, pVertexData, sizeof(SVertexTypeColor) * _count);
    //    }

    //    return FALSE;
    //}


    //BOOL RenderLayer::UpdateVertexBuffer(const IVertexBuffer* pVertexBuffer, const SVertexTypeTexture* pVertexData, size_t _count)
    //{
    //    if(m_pRenderDevice)
    //    {
    //        return m_pRenderDevice->UpdateVertexBuffer(pVertexBuffer, pVertexData, sizeof(SVertexTypeTexture) * _count);
    //    }

    //    return FALSE;
    //}

    //void RenderLayer::DestroyVertexBuffer(IVertexBuffer** pVertexBuffer)
    //{
    //    if(m_pRenderDevice)
    //    {
    //        return m_pRenderDevice->DestroyVertexBuffer(pVertexBuffer);
    //    }
    //}

    ITexture* RenderLayer::CreateTextureFromFile(const WCHAR* filename)
    {
        if(m_pRenderDevice)
        {
            return m_pRenderDevice->CreateTextureFromFile(filename);
        }
        
        return nullptr;
    }

    ITexture* RenderLayer::CreateTextureFromMemory(const void* data, size_t _size)
    {
        if(m_pRenderDevice)
        {
            return m_pRenderDevice->CreateTextureFromMemory(data, _size);
        }

        return nullptr;
    }

    ITexture* RenderLayer::CreateTexture(UINT w, UINT h)
    {
        if(m_pRenderDevice)
        {
            return m_pRenderDevice->CreateTexture(w, h);
        }

        return nullptr;
    }

    void RenderLayer::DestroyTexture(ITexture** pTexture)
    {
        if(m_pRenderDevice)
        {
            m_pRenderDevice->DestroyTexture(pTexture);
        }
    }



    //////////////////////////////////////////////////////////////////////////

    // 画一组点
    void RenderLayer::DrawPoints(const SVertexTypeColor* pPoints,  UINT _count)
    {
        if(m_pRenderDevice)
        {
            IVertexBuffer* pVertexBuffer = m_pRenderDevice->CreateVertexBuffer(pPoints, _count * sizeof(SVertexTypeColor));
            m_pRenderDevice->DrawVertex(pVertexBuffer, nullptr, _count, 0, eRenderMode_Point );
            m_pRenderDevice->DestroyVertexBuffer(&pVertexBuffer);
        }
    }

    // 画一组线带
    void RenderLayer::DrawLineTrip(const SVertexTypeColor* pPoints, UINT _count)
    {
        if(m_pRenderDevice)
        {
            IVertexBuffer* pVertexBuffer = m_pRenderDevice->CreateVertexBuffer(pPoints, _count * sizeof(SVertexTypeColor));
            m_pRenderDevice->DrawVertex(pVertexBuffer, nullptr, _count, 0, eRenderMode_LineTrip);
            m_pRenderDevice->DestroyVertexBuffer(&pVertexBuffer);
        }
    }
    
    // 画色块
    void RenderLayer::DrawTriangleTrip(const SVertexTypeColor* pPoints, UINT _count)
    {
        if(m_pRenderDevice)
        {
            IVertexBuffer* pVertexBuffer = m_pRenderDevice->CreateVertexBuffer(pPoints, _count * sizeof(SVertexTypeColor));
            m_pRenderDevice->DrawVertex(pVertexBuffer, nullptr, _count, 0, eRenderMode_triangleTrip);
            m_pRenderDevice->DestroyVertexBuffer(&pVertexBuffer);
        }
    }

    // 画一个点
    void RenderLayer::DrawPoint(int x, int y, D3DXCOLOR color)
    {
        const RECT& rt = LibGraphics_GetWinGameApp()->GetWindowClientRect();

        float fx   = (float)(((rt.right - rt.left) / 2) * -1) + static_cast<float>(x);
        float fy   = (float)((rt.bottom - rt.top) / 2) - static_cast<float>(y);

        SVertexTypeColor InputVertex;
        InputVertex.position = D3DXVECTOR3((float)fx, (float)fy, (float)0);
        InputVertex.color = color;

        DrawPoints(&InputVertex, 1);
    }

    // 画一条线
    void RenderLayer::DrawLine(int x1, int y1, int x2, int y2, D3DXCOLOR color)
    {
        const RECT& rt = LibGraphics_GetWinGameApp()->GetWindowClientRect();

        float fx1   = (float)(((rt.right - rt.left) / 2) * -1) + static_cast<float>(x1);
        float fy1   = (float)((rt.bottom - rt.top) / 2) - static_cast<float>(y1);
        float fx2   = (float)(((rt.right - rt.left) / 2) * -1) + static_cast<float>(x2);
        float fy2   = (float)((rt.bottom - rt.top) / 2) - static_cast<float>(y2);

        SVertexTypeColor InputVertex[2];
        InputVertex[0].position = D3DXVECTOR3((float)fx1, (float)fy1, (float)0);
        InputVertex[0].color    = color;
        InputVertex[1].position = D3DXVECTOR3((float)fx2, (float)fy2, (float)0);
        InputVertex[1].color    = color;

        DrawLineTrip(&InputVertex[0], 2);
    }

    // 画矩形
    void RenderLayer::DrawRect(int x, int y, int w, int h, const D3DXCOLOR& color)
    {
        const RECT& rt = LibGraphics_GetWinGameApp()->GetWindowClientRect();
        
        float left    = (float)(((rt.right - rt.left) / 2) * -1) + static_cast<float>(x);
        float right   = left + (float)w;
        float top     = (float)((rt.bottom - rt.top) / 2) - static_cast<float>(y);
        float bottom  = top - (float)h;

        // 顶点从左上角开始顺时针方向数
        SVertexTypeColor InputVertex[5];
        InputVertex[0].position = D3DXVECTOR3(float(left), float(top), (float)0);
        InputVertex[0].color    = color;
        InputVertex[1].position = D3DXVECTOR3(float(right), float(top), (float)0);
        InputVertex[1].color    = color;
        InputVertex[2].position = D3DXVECTOR3(float(right), float(bottom), (float)0);
        InputVertex[2].color    = color;        
        InputVertex[3].position = D3DXVECTOR3(float(left), float(bottom), (float)0);
        InputVertex[3].color    = color;
        InputVertex[4].position = D3DXVECTOR3(float(left), float(top), (float)0);
        InputVertex[4].color    = color;

        DrawLineTrip(&InputVertex[0], 5);
    }


    // 填充矩形
    void RenderLayer::FillRect(int x, int y, int w, int h, const D3DXCOLOR& color)
    {
        const RECT& rt = LibGraphics_GetWinGameApp()->GetWindowClientRect();

        float left    = (float)(((rt.right - rt.left) / 2) * -1) + static_cast<float>(x);
        float right   = left + (float)w;
        float top     = (float)((rt.bottom - rt.top) / 2) - static_cast<float>(y);
        float bottom  = top - (float)h;

        // 顶点从左上角开始顺时针方向数
        SVertexTypeColor InputVertex[5];
        InputVertex[0].position = D3DXVECTOR3(float(left), float(top), (float)0);
        InputVertex[0].color    = color;
        InputVertex[1].position = D3DXVECTOR3(float(right), float(top), (float)0);
        InputVertex[1].color    = color;
        InputVertex[2].position = D3DXVECTOR3(float(right), float(bottom), (float)0);
        InputVertex[2].color    = color;        
        InputVertex[3].position = D3DXVECTOR3(float(left), float(bottom), (float)0);
        InputVertex[3].color    = color;
        InputVertex[4].position = D3DXVECTOR3(float(left), float(top), (float)0);
        InputVertex[4].color    = color;

        DrawTriangleTrip(&InputVertex[0], 5);
    }


    // 画纹理
    void RenderLayer::DrawTextureRect(int x, int y, int width, int height, const ITexture* pTexture, const skyRect& rtClip, float alpha)
    {
        if(!pTexture)
        {
            return;
        }

        if(width == 0)
        {
            width = rtClip.w;
        }

        if(height == 0)
        {
            height = rtClip.h;
        }

        UINT wTex = pTexture->GetWidth();
        UINT hTex = pTexture->GetHeight();

        const RECT& rt = LibGraphics_GetWinGameApp()->GetWindowClientRect();

        float left    = (float)(((rt.right - rt.left) / 2) * -1) + static_cast<float>(x);
        float right   = left + (float)width;
        float top     = (float)((rt.bottom - rt.top) / 2) - static_cast<float>(y);
        float bottom  = top - (float)height;

        float fPosX1 = (float)rtClip.x / wTex;
        float fPosY1 = (float)rtClip.y / hTex;
        float fPosX2 = fPosX1 + (float)rtClip.w / wTex;
        float fPosY2 = fPosY1 + (float)rtClip.h / hTex;

        const UINT nVerNum = 4;
        SVertexTypeTexture vertices[nVerNum];
        vertices[0].position    = D3DXVECTOR3(left, top, 0.0f);
        vertices[0].texture     = D3DXVECTOR2(fPosX1, fPosY1);
        vertices[1].position    = D3DXVECTOR3(right, top, 0.0f);
        vertices[1].texture     = D3DXVECTOR2(fPosX2, fPosY1);
        vertices[2].position    = D3DXVECTOR3(left, bottom, 0.0f);
        vertices[2].texture     = D3DXVECTOR2(fPosX1, fPosY2);
        vertices[3].position    = D3DXVECTOR3(right, bottom, 0.0f);
        vertices[3].texture     = D3DXVECTOR2(fPosX2, fPosY2);

        m_pRenderDevice->UpdateVertexBuffer(m_pVertexBuffer, vertices, 4 * sizeof(SVertexTypeTexture));
        m_pRenderDevice->DrawVertex(m_pVertexBuffer, pTexture, 4, 0, eRenderMode_texture);
        
        //if(m_pRenderDevice)
        //{
        //    IVertexBuffer* pVertexBuffer = m_pRenderDevice->CreateVertexBuffer(vertices, 4 * sizeof(SVertexTypeTexture));
        //    m_pRenderDevice->DrawVertex(pVertexBuffer, pTexture, 4, 0, eRenderMode_texture);
        //    m_pRenderDevice->DestroyVertexBuffer(&pVertexBuffer);
        //}
    }


    void RenderLayer::DrawTexture(int x, int y, const ITexture* pTexture, float alpha)
    {
        skyRect rect(0, 0, pTexture->GetWidth(), pTexture->GetHeight());
        DrawTextureRect(x, y, 0, 0, pTexture, rect, alpha);
    }


    void RenderLayer::DrawTexture(int x, int y, int width, int height, const ITexture* pTexture, float alpha)
    {
        skyRect rect(0, 0, pTexture->GetWidth(), pTexture->GetHeight());
        DrawTextureRect(x, y, width, height, pTexture, rect, alpha);
    }

    BOOL RenderLayer::RenderString(const TextPanel* pTextPanel, const char* pText, const STextAttrib* pAttrib)
    {
        if(m_pRenderDevice)
        {
            return m_pRenderDevice->RenderString(pTextPanel, pText, pAttrib);
        }
        return FALSE;
    }

    BOOL RenderLayer::RenderText(int x ,int y, const char* pText)
    {
        TextPanel panel;
        panel.CreateTextPanel(200, 300);
        panel.RenderString(pText);
        panel.Draw(x, y, 0, 0);
        panel.Release();
        return TRUE;
    }

}
