#pragma once

#include "Math.h"

/*
������Ⱦ�豸;
*/

namespace LibEngine
{
    enum eRenderMode
    {
        eRenderMode_Point,              // ��
        eRenderMode_LineTrip,           // �ߴ�
        eRenderMode_triangleTrip,       // ������(��ɫ��)
        eRenderMode_texture,            // ����

    };

    struct  ITexture;
    struct  IVertexBuffer;
    enum    E_WINDOW_MODE;

    class   TextPanel;
    struct  STextAttrib;

    // ��ͬ��Ⱦ�豸�Ļ���;
    struct IRenderDevice
    {
        // ��ʼ��������
        virtual bool                Init(HWND hWnd, E_WINDOW_MODE mode) = 0;
        virtual void                Release() = 0;

        virtual void                BeginRender(float red, float green, float blue, float alpha) = 0;
        virtual void                EndRender() = 0;


        // ��������        
        virtual void                DrawVertex(const IVertexBuffer* pVertexBuffer, const ITexture* pTexture,
            UINT _count, UINT _index, eRenderMode _mode) = 0;


        virtual IVertexBuffer*      CreateVertexBuffer(const void* pData, UINT nByteWidth) = 0;
        virtual BOOL                UpdateVertexBuffer(const IVertexBuffer* pVertexBuffer, const void* pData, UINT nByteWidth) = 0;
        virtual void                DestroyVertexBuffer(IVertexBuffer** ppVertexBuffer) = 0;

        // ����;
        virtual ITexture*           CreateTextureFromFile(const WCHAR* filename) = 0;
        virtual ITexture*           CreateTextureFromMemory(const void* data, size_t _size) = 0;
        virtual ITexture*           CreateTexture(UINT w, UINT h) = 0;
        virtual void                DestroyTexture(ITexture** pTexture) = 0;
        
        virtual BOOL                RenderString(const TextPanel* pTextPanel, const char* pText, const STextAttrib* pAttrib) = 0;

    };

}
