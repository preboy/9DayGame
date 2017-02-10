#include "stdafx.h"
#include "LibCore/timer.h"
#include "singleton.h"
#include <MMSystem.h>

namespace LibCore
{

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
        TimerObject* p = _find_timer(dwTimerID);
        if (p)
        {
            p->bDel = true;
        }
    }

    DWORD Timer::CreateTimer( UINT nMsec, static_timer_func func, LPVOID lParam, bool bRpt ) 
    {
        timer_object<Timer>* ptr = new timer_object<Timer>;
        ptr->init(nMsec, func, lParam, bRpt);
        m_lst_Object.push_back(ptr);

        return ptr->nTimerID;
    }

    TimerObject* Timer::_find_timer(DWORD dwTimerID)
    {
        for(auto it = m_lst_Object.begin(), itor = m_lst_Object.end(); it != itor; it++)
        {
            if ( dwTimerID == (*it)->nTimerID )
            {
                return (*it);
            }
        }
        return nullptr;
    }

    void Timer::SetTimerInterval(DWORD dwTimerID)
    {
        TimerObject* p = _find_timer(dwTimerID);
        if (p)
        {
            p->nInterval = dwTimerID;
        }
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

}