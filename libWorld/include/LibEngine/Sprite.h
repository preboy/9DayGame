#pragma once
 
namespace LibEngine
{
    // 可显示物件，如图片 动画的基类;
    struct ISprite
    {

        // 在指定位置区域，显示图片，图片会被自动放大缩小;
        virtual void    Draw(short x, short y, USHORT width, USHORT height) = 0;
        virtual void    Release() = 0;
    };

}