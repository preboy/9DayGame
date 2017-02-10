#pragma once
#include "timer_object.h"

#include <list>
using namespace std;

namespace LibEngine
{
	// 单件，管理定时器链表的类
	class Timer
	{
	public:
		Timer();
	   ~Timer();
            
	public:

        bool Init();
        void Release();

        // 对所有的定时器做一次检测;
        void Run();

        // 删除定时器
        void KillTimer( DWORD dwTimerID );
        
        // 增加一个定时器;
        DWORD CreateTimer( UINT nInterval, static_timer_func func, LPVOID lParam, bool bRpt = true );

        template<typename T>
        DWORD CreateTimer( UINT nMsec, T* ptr, typename timer_object<T>::TIMER_CALLBACK func, LPVOID lParam , bool bRpt = true)
        {
            timer_object<T>* p = new timer_object<T>;
            p->init(nMsec, ptr, func, lParam, bRpt);
            m_lst_Object.push_back(p);

            return p->nTimerID;
        }

	private:
        std::list<TimerObject*>    m_lst_Object;
    };

}























