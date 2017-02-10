#pragma once

// 主要是申明文件
namespace LibGraphics
{
    enum E_WINDOW_MODE                  // 游戏窗口模式
    {
        E_WINDOW_MODE_FULL_SCREEN,      // 全屏(分辨率取自最大)
        E_WINDOW_MODE_FULL_WINDOWS,     // 全窗口(分辨率取自最大)
        E_WINDOW_MODE_CUSTOM,           // 定制模式大小(分辨率取自窗口大小)
    };

    enum E_FONT_TYPE
    {
        FONT_TYPE_NORMAL         = 0, // 普通字体;
        FONT_TYPE_MAX,
    };


};