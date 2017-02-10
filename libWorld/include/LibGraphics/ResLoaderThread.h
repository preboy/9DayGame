#pragma once

#include "LibWindows/thread_base.h"
using namespace LibWindows;

namespace LibGraphics
{
	class ResLoaderThread : public thread_base
	{
	public:
		ResLoaderThread();
	   ~ResLoaderThread();

	protected:
		virtual bool		Run();
        virtual bool		OnThreadEnter();
        virtual void		OnThreadLeave();
	};
}