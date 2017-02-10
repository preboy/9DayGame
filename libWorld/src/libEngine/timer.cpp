#include "stdafx.h"
#include "LibEngine/timer.h"
#include "LibEngine/singleton.h"
#include <MMSystem.h>

using namespace LibEngine;


Timer::Timer()
{
}

Timer::~Timer()
{
    Release();
}

bool Timer::Init()
{
    return true;
}

void Timer::Release()
{
    for(auto it = m_lst_Object.begin(), itor = m_lst_Object.end(); it != itor; it++)
    {
        delete (*it);
        (*it) = nullptr;
    }
    m_lst_Object.clear();
}


void Timer::KillTimer( DWORD dwTimerID )
{
    for(auto it = m_lst_Object.begin(), itor = m_lst_Object.end(); it != itor; it++)
    {
        if ( dwTimerID == (*it)->nTimerID )
        {
            (*it)->bDel = true;
            break;
        }
    }
}


DWORD Timer::CreateTimer( UINT nMsec, static_timer_func func, LPVOID lParam, bool bRpt ) 
{
    timer_object<Timer>* ptr = new timer_object<Timer>;
    ptr->init(nMsec, func, lParam, bRpt);
    m_lst_Object.push_back(ptr);

    return ptr->nTimerID;
}


void Timer::Run()
{
    DWORD dwTime = ::timeGetTime();
    for(auto it = m_lst_Object.begin(), itor = m_lst_Object.end(); it != itor; )
    {
        if((*it)->bDel)
        {
            delete (*it);
            it = m_lst_Object.erase(it);
            continue;
        }

        if((*it)->is_timeout(dwTime))
        {
            (*it)->exec(dwTime);
            if( (*it)->bDel || !(*it)->bRepeat )
            {
                delete (*it);
                it = m_lst_Object.erase(it);
                continue;
            }
        }

        it++;
    }
}

