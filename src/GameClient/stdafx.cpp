// stdafx.cpp : 只包括标准包含文件的源文件
// GameClient.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"

// TODO: 在 STDAFX.H 中
// 引用任何所需的附加头文件，而不是在此文件中引用

#pragma comment(lib, "LibXML.lib")
#pragma comment(lib, "LibWindows.lib")
#pragma comment(lib, "LibNetwork.lib")
#pragma comment(lib, "LibEngine.lib")
#pragma comment(lib, "LibGraphics.lib")
#pragma comment(lib, "LibSound.lib")
#pragma comment(lib, "LibFS.lib")

#ifdef _DEBUG
#pragma comment(lib, "freetype2410MT_D.lib")
#else
#pragma comment(lib, "freetype2410MT.lib")
#endif

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")

// #pragma comment(lib, "XAudio2.lib")