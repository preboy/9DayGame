// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�
#include <WinSock2.h>
#include <windows.h>

#include "pub_protocol.h"
using namespace NetProt;

#include "pub_struct.h"
#include "pub_macro.h"

#include "LibEngine/singleton.h"
using namespace LibEngine;

#include "Src/DB_cmdInput.h"

#include "Src/DB_TCP_Client_GS.h"
#include "Src/DB_TCP_Server_LS.h"


using namespace DBServer;


#include "pub_typedef.h"