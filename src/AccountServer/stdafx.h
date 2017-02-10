// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



// TODO: 在此处引用程序需要的其他头文件;
#include <WinSock2.h>
#include <windows.h>
#include "pub_protocol.h"
using namespace NetProt;

#include "pub_struct.h"
#include "pub_macro.h"

#include "LibEngine/singleton.h"
using namespace LibEngine;

#include "src/AS_TCP_Server_GS.h"
#include "Src/AS_cmdInput.h"
using namespace AccountServer;


#include "pub_typedef.h"