#pragma once

namespace LibEngine
{
	template< typename T>
	class singleton2
	{
	protected:
		singleton2()
		{
		}

		~singleton2()
		{
		}

		static void createInstance()
		{
			if (nullptr == sptr)
			{
				sptr = new T();
			}
		}	

        static void releaseInstance()
        {
            if(sptr)
            {
                delete sptr;
                sptr = nullptr;
            }
        }

        static void getInstance()
        {
            return sptr;
        }

	private:
		static T* sptr;
	};

    template<typename T> T* singleton2<T>::sptr = nullptr;


#define MAKE_SINGLETON(CLS) friend class singleton2<CLS>;

#define INSTANCE2(CLS) singleton2<CLS>::getInstance()

};
