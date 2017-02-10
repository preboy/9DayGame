// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             //  �� Windows ͷ�ļ����ų�����ʹ�õ���Ϣ
// Windows ͷ�ļ�:
#include <windows.h>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

// C ����ʱͷ�ļ�
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <assert.h>

// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�
#include <dxgi.h>
#include <D3DX11.h>
#include <d3dcommon.h>
#include <d3dx10math.h>

#include "LibEngine/singleton.h"
using namespace LibEngine;


#include "src/GameState_Logo.h"
#include "src/GameState_Login.h"
using namespace GameClient;

#include "LibGraphics/LibGraphics.h"
using namespace LibGraphics;

#include "pub_macro.h"
#include "pub_typedef.h"