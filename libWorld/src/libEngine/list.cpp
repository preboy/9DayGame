#include "StdAfx.h"
#include "LibEngine/list.h"

using namespace LibEngine;

list_ring::list_ring()
{
	m_pHead			= nullptr;
	m_pTail			= nullptr;
	m_uNodeCount	= 0;
	m_uUse			= 0;
}

list_ring::~list_ring()
{
}

bool list_ring::add_nodes( node* pNode, USHORT uHeadSize, USHORT uBuffSize, USHORT uNode )
{
	node* pTemp	= pNode;
	for(USHORT i=0; i< uNode; ++i )
	{
		pTemp->pNext = new node;
		pTemp->pNext->init( uHeadSize, uBuffSize );
		pTemp = pTemp->pNext;
		++m_uNodeCount;
	}
	pTemp->pNext = pNode;
	return true;
}

bool list_ring::init( USHORT uHeadSize, USHORT uBuffSize, USHORT uNode )
{
	m_pHead			= new node;
	m_pHead->init( uHeadSize, uBuffSize );
	m_uNodeCount	= 1;
	add_nodes( m_pHead, uHeadSize, uBuffSize, uNode );
	m_pTail			= m_pHead;
	return true;
}

bool list_ring::release()
{
	if ( !is_emputy() )
	{
		 return false;
	}
	node* pNode		= m_pHead;
	node* pNodeTmp	= nullptr;

	do
	{
		pNode->release();
		pNode = pNode->pNext;
	}while( pNode != m_pHead );

	pNode = m_pHead->pNext;
	m_pHead->pNext = nullptr;
	while( pNode != m_pHead )
	{
		pNodeTmp	= pNode;
		pNode		= pNode->pNext;
		delete		pNodeTmp;
	}

	delete	m_pHead;
	m_pHead = nullptr;
	m_pTail	= nullptr;
	return	true;
}

bool list_ring::is_emputy()
{
	return m_pHead == m_pTail;
}

bool list_ring::is_full()
{
	return m_pHead->pNext == m_pTail;
}

USHORT list_ring::get_count()
{
	return m_uNodeCount;
}

USHORT list_ring::get_use_count()
{
	return m_uUse;
}

node* list_ring::get_node_for_push()
{
	if ( is_full() )
	{
		 return false;
	}
	return m_pHead;
}

node* list_ring::get_node_for_handle()
{
	if ( is_emputy() )
	{
		 return nullptr;
	}
	return m_pTail;
}

int list_ring::set_node_push_completion(node* pNode)
{
	m_pHead = m_pHead->pNext;
	return 0;
}

int list_ring::set_node_handle_completion(node* pNode)
{
	m_pTail = m_pTail->pNext;
	return 0;
}
