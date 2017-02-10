#pragma once
#include "timer_object.h"

#include <list>
using namespace std;

namespace LibEngine
{
	// ����������ʱ���������
	class Timer
	{
	public:
		Timer();
	   ~Timer();
            
	public:

        bool Init();
        void Release();

        // �����еĶ�ʱ����һ�μ��;
        void Run();

        // ɾ����ʱ��
        void KillTimer( DWORD dwTimerID );
        
        // ����һ����ʱ��;
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























