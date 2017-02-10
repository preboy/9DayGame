#include "stdafx.h"
#include "LibEngine/hashcode.h"

namespace LibEngine
{
	inline unsigned int GetHashCode(const char *str)
	{
		register unsigned int		h	=0;
		register unsigned char *p = NULL; 
		for(h=0, p = (unsigned char *)str; *p ; p++)
		{
			h = 31 * h + *p; 
		}
		return h;
	}

}

namespace LibEngine
{
	template<typename T>
	HashTable<T>::HashBody::HashBody()
	{
		pPointer	=	NULL;
		pNext		= NULL;
	}

	template<typename T>
	HashTable<T>::HashNode::HashNode()
	{
		pBody		= NULL;
	}

	template<typename T>
	HashTable<T>::HashHead::HashHead()
	{
			wItemNum	= 0;
			pNode			= 0;
			pList				= 0;
	}
	




}

