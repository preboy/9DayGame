#pragma once

namespace LibEngine
{
#define SYS_TYPE 0

	// 产生一个单件
	template< typename T, USHORT type = SYS_TYPE >
	class singleton
	{
	public:
		singleton()
		{
			m_Tptr = nullptr;
		}

		~singleton()
		{
			if ( m_Tptr )
			{
				delete m_Tptr;
				m_Tptr = nullptr;
			}
		}

		static T* getInstance()
		{
			static singleton<T> i;
			if ( nullptr == i.m_Tptr )
			{
				i.m_Tptr = new T();
			}
			return i.m_Tptr;
		}	
	private:
		T* m_Tptr;
	};

#define INSTANCE( CLASS ) singleton<CLASS>::getInstance()

};
