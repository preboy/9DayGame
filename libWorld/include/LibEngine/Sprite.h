#pragma once
 
namespace LibEngine
{
    // ����ʾ�������ͼƬ �����Ļ���;
    struct ISprite
    {

        // ��ָ��λ��������ʾͼƬ��ͼƬ�ᱻ�Զ��Ŵ���С;
        virtual void    Draw(short x, short y, USHORT width, USHORT height) = 0;
        virtual void    Release() = 0;
    };

}