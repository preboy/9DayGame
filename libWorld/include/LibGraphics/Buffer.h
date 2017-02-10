#pragma once

namespace LibGraphics
{
    // ���㻺��
    struct IVertexBuffer
    {
        enum eVertexType
        {
            eVertexType_Color,       // ��ɫ����
            eVertexType_Texture,     // ������
        };

        virtual ~IVertexBuffer(){};

        // �ͷ�ʱ����;
        virtual void            Release() = 0;
    };


    // ��������
    struct IIndexBuffer
    {
        virtual void            Release() = 0;
    };

}
