#pragma once

#include "LibCore/thread_base.h"
using namespace LibCore;

namespace LibEngine
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