#pragma once
#include <new>
#include <vector>
#undef new

using namespace std;

namespace LibEngine
{
	// 头信息
#pragma pack(push)
#pragma pack(1)
	struct ItemHead
	{
		USHORT uUSE;	// 表明该Item是否正用, 0表示未使用 1表示使用
		USHORT uPos;	// 在chunk索引表中的位置

	public:
		ItemHead()
		{
			clear_state();
		}
		void clear_state()
		{
			uUSE = 0;
		}
		void set_state()
		{
			uUSE = 1;
		}
		USHORT get_state()
		{
			return uUSE;
		}
		USHORT get_pos()
		{
			return uPos;
		}
		void set_pos( USHORT pos )
		{
			uPos = pos;
		}
	};
#pragma pack(pop)

#define CONTAINER( CLASS )	\
public:					    \
	USHORT	m_uID;			\
public:						\
	USHORT	get_id()		\
	{						\
	return	m_uID;			\
	}						\
	friend	class hash_table<CLASS>;


	// 自定义的一种存取方式，取名叫hash_table吧，其实我都不知道hash_table是什么意思。
	template< typename T>
	class hash_table
	{
	public:
		typedef DWORD (WINAPI* pHash_Table_Func)( T* );
		typedef T this_type;
	private:
		// 一个chunk块存储100个Item项，每一项前面都有一个ItemHead
		struct chunk 
		{
		private:
			USHORT	uItemUse;		// 使用中的Item的数量
			USHORT	uItemCount;		// 共有多少个Item	
			USHORT	uItemSize;		// 一个item+head有多大
			USHORT	uIndex;			// block索引
			BYTE*	pPtr;
		public:
			chunk()
			{
				memset(this, 0x0, sizeof(chunk));
			}
			~chunk()
			{
			}
			USHORT get_index()
			{
				return uIndex;
			}
			void add_blockNumber()
			{
				++uItemUse;
			}
			void sub_blockNumber()
			{
				--uItemUse;
			}
			bool init( USHORT uItemPerChunk, USHORT uI )
			{
				uItemUse	= 0;
				uIndex		= uI;
				uItemCount	= uItemPerChunk;
				uItemSize	= sizeof(ItemHead) + sizeof(T);
				pPtr		= new BYTE[uItemSize*uItemCount];
				memset( pPtr, 0x0, uItemSize*uItemCount );
				ItemHead* phead = nullptr;
				for( USHORT i=0; i<uItemPerChunk; ++i )
				{
					phead = reinterpret_cast<ItemHead*>(pPtr+(i*uItemSize));
					phead->set_pos( i );
				}
				return true;
			}
			bool release()
			{
				if ( pPtr )
				{
					delete[] pPtr;
					pPtr = nullptr;
				}
				memset(this, 0x0, sizeof(chunk));
				return true;
			}
			bool is_full()
			{
				return uItemUse == uItemCount;
			}
			bool is_empty()
			{
				return uItemUse == 0;
			}
			ItemHead* get_block()
			{
				if ( is_full() || pPtr == nullptr )
				{
					return nullptr;
				}
				ItemHead* pHead = nullptr;
				for( USHORT i =0; i< uItemCount; ++i)
				{
					pHead = reinterpret_cast<ItemHead*>(pPtr+(i*uItemSize));
					if ( pHead->uUSE == 0 )
					{
						return pHead;
					}
				}
				return nullptr;
			}
			ItemHead* get_block( USHORT uNO )
			{
				if ( is_empty() || pPtr == nullptr || uNO >= uItemCount )
				{
					return nullptr;
				}
				return reinterpret_cast<ItemHead*>(pPtr+(uItemSize*uNO));
			}

			DWORD for_each( pHash_Table_Func func )
			{
				DWORD dwRet		= 0;
				DWORD dwCount	= 0;
				if ( uItemUse == 0 ) return 0;
				ItemHead* phead	= nullptr;
				for( USHORT i=0; i< uItemCount; i++)
				{
					phead = pPtr+(i*uItemSize);
					if ( phead->get_state() )
					{
						dwRet = (*func)(reinterpret_cast<T*>(phead+1));
						if ( dwRet ) return dwRet;
					}
				}
				return 0;
			}
		};

	private:
		vector<chunk*>	m_vChunk;
		USHORT			m_uChunkCount;	// 共多少个chunk块
		USHORT			m_uItemPerChunk;// 每一个chunk有多少个item
		USHORT			m_uUseItem;		// 使用中的item数

	public:
		hash_table()
		{
			m_uChunkCount	= 0;
			m_uItemPerChunk	= 0;
			m_uUseItem		= 0;
		}
		~hash_table()
		{
		}
		bool add_chunk( USHORT uIndex )
		{
			chunk* pchk = new chunk;
			pchk->init( m_uItemPerChunk, uIndex );
			m_vChunk.push_back( pchk );
			++m_uChunkCount;
			return true;
		}

		bool init( USHORT uChunkCount = 100, USHORT uItemPerChunk = 100 )
		{
			m_uItemPerChunk	= uItemPerChunk;
			for(USHORT i = 0; i<uChunkCount; ++i)
			{
				add_chunk( i );
			}
			return true;
		}
		bool release()
		{
			USHORT uSize = m_vChunk.size();
			for( USHORT i=0; i<uSize; i++ )
			{
				m_vChunk[i]->release();
				delete m_vChunk[i];
				m_vChunk[i] = nullptr;
			}
			m_vChunk.clear();
			return true;
		}

		// 插入一个新的T时寻找一块内存
		T* insert()
		{
			chunk* pchk = get_chunk();
			if ( pchk == nullptr )
			{
				return nullptr;
			}
			ItemHead*	pHead	= pchk->get_block();
			char*	pByte		= reinterpret_cast<char*>(pHead+1);		
			T*		pNewT	 	= new(pByte)T;
			USHORT	uID			= pchk->get_index()*m_uItemPerChunk + pHead->get_pos()+1;
			pNewT->m_uID			= uID;
			pHead->set_state();
			pchk->add_blockNumber();
			m_uUseItem++;
			return pNewT;
		}
		// 删掉一个T
		bool del( USHORT uID )
		{
			if ( uID == 0 || uID >= m_uChunkCount*m_uItemPerChunk )
			{
				return nullptr;
			}
			USHORT indexChunk	= uID / m_uItemPerChunk;
			USHORT indexItem	= uID % m_uItemPerChunk;
			if ( indexItem == 0 )
			{
				indexChunk--;
				indexItem = m_uItemPerChunk;
			}
			indexItem--;
			chunk* pchk			= get_chunk( indexChunk );
			ItemHead* pHead		= pchk->get_block(indexItem);
			
			T* pItem = reinterpret_cast<T*>(pHead+1);
			if ( !pItem )	return true;
			pItem->~T();
			memset( pItem, 0x0, sizeof(T) );
			pHead->clear_state();
			pchk->sub_blockNumber();
			m_uUseItem--;
			return true;
		}

		T* find( USHORT uID )
		{
			if ( uID == 0 || uID >= m_uChunkCount*m_uItemPerChunk )
			{
				return nullptr;
			}
			USHORT indexChunk	= uID / m_uItemPerChunk;
			USHORT indexItem	= uID % m_uItemPerChunk;
			if ( indexItem == 0 )
			{
				indexChunk--;
				indexItem = m_uItemPerChunk;
			}
			indexItem--;
			chunk* pchk			= get_chunk( indexChunk );
			ItemHead* pHead		= pchk->get_block(indexItem);
			return reinterpret_cast<T*>(pchk+1);
		}

		chunk* get_chunk()
		{
			for( USHORT i=0; i<m_vChunk.size(); i++ )
			{
				if ( m_vChunk[i]->is_full() )
				{
					continue;
				}
				return m_vChunk[i];
			}
			return nullptr;
		}

		// 获取一个chunk
		chunk* get_chunk( USHORT i )
		{
			if ( i >= m_vChunk.size() )
			{
				return nullptr;
			}
			if ( m_vChunk[i]->get_index() != i )
			{
				return nullptr;
			}
			return m_vChunk[i];
		}

		DWORD for_each( pHash_Table_Func func )
		{
			DWORD dwRet;
			if ( !func )	return;
			if ( m_uUseItem == 0 ) return 0;
			for(USHORT i=0; i<m_vChunk.size(); ++i )
			{
				dwRet = m_vChunk[i]->for_each( func );
				if ( dwRet ) 	return dwRet;
			}
			return 0;
		}
	};
}

