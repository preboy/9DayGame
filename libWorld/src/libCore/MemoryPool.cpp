#include "StdAfx.h"
#include "LibCore/MemoryPool.h"
namespace LibCore
{
    template< typename T, int nType>
    FixMemAllocer<T, nType>::FixBlock::FixBlock()
    {
        wState      = 0;
        wIndex      = 0;
        pBlockNext  = NULL;
    }

    template< typename T, int nType>
    T* FixMemAllocer<T, nType>::FixBlock::GetDataPtr()
    {
        return reinterpret_cast<T*>(this+1);
    }

    template< typename T, int nType>
    typename FixMemAllocer<T, nType>::FixChunk* FixMemAllocer<T, nType>::FixBlock::GetChunkHead()
    {
        return static_cast<FixChunk*>( (UINT)(*&this) - wIndex * ( _wItemSize + sizeof(FixBlock) ) - sizeof(FixChunk) );
    }


    template< typename T, int nType>
    FixMemAllocer<T, nType>::FixChunk::FixChunk()
    {
        wByteSize    = 0;
        wTotalBlock  = 0;
        wUseBlock    = 0;
        pChunkNext   = NULL;
    }

    template< typename T, int nType>
    typename FixMemAllocer<T, nType>::FixChunk* FixMemAllocer<T, nType>::FixChunk::GetBlockHead( UINT nIndex )
    {
        if ( nIndex >= wTotalBlock )
        {
            return NULL;
        }
        return reinterpret_cast<FixChunk*>( (this+1) + nIndex*( _wItemSize + sizeof(FixBlock)) );
    }

    template< typename T, int nType>
    void  FixMemAllocer<T, nType>::FixChunk::InitChunk(    UINT nSize )
    {
        wByteSize   = nSize;
        wTotalBlock = nSize / ( sizeof( FixBlock ) + _wItemSize );
        wUseBlock   = 0;
        FixChunk* pTmpBok = GetBlockHead( 0 );
        UINT i = 0;
        while( i < wTotalBlock - 1 )
        {
            pTmpBok->wState        = BLOCK_NOUSE;
            pTmpBok->wIndex        = i;
            pTmpBok->pBlockNext = pTmpBok + sizeof(FixBlock) + _wItemSize;
            pTmpBok = pTmpBok->pBlockNext;
            i++;
        }
        pTmpBok->wState = BLOCK_NOUSE;
        pTmpBok->wIndex = i;
    }


    template< typename T, int nType>
    typename FixMemAllocer<T, nType>::FixChunk*  FixMemAllocer<T, nType>::FixChunk::Alloc()
    {
        if ( wUseBlock >= wTotalBlock )
        {
            return NULL;
        }
        FixChunk* pBok = NULL;
        for( int i=0; i< wTotalBlock; i++ )
        {
            pBok = GetBlockHead( i );
            if ( pBok->wState == BLOCK_NOUSE )
            {
                return pBok;
            }
        }
        return NULL;
    }


    template< typename T, int nType>
    void  FixMemAllocer<T, nType>::FixChunk::Clear()
    {
        wState = BLOCK_NOUSE;
        ::ZeroMemory( pBlock->GetDataPtr(), _wItemSize );
    }


    template< typename T, int nType>
    FixMemAllocer<T, nType>::FixMemAllocer( )
    {
        _nChunkSize        = 64 * 1024;        // 10K
        _pFirstChunk    = NULL;
        UINT t = sizeof(T) % 4;                // 每一块以4字节对齐
        if ( t != 0 )
        {
            _wItemSize = sizeof(T) + 4 - t;
        }
        else
        {
            _wItemSize = sizeof(T);
        }
    }

    template< typename T, int nType>
    FixMemAllocer<T, nType>::~FixMemAllocer( )
    {

    }

    template< typename T, int nType>
    T*    FixMemAllocer<T, nType>::Alloc( )
    {
        FixChunk* pTmpChk = _pFirstChunk;
        while( pTmpChk )
        {
            if ( pTmpChk->wUseBlock < pTmpChk->wTotalBlock )
            {
                pTmpChk->wUseBlock++;
                return pTmpChk->Alloc()->GetDataPtr();
            }
            pTmpChk = pTmpChk->pChunkNext;
        }
        AppendChunk();
        return Alloc();
    }

    template< typename T, int nType>
    bool    FixMemAllocer<T, nType>::Release( T* pItem )
    {
        FixChunk* pBlock = GetBlockPtr( pItem );
        if ( pBlock )
        {
            pBlock->Clear();
            pBlock->GetChunkHead()->wUseBlock--;
            return true;
        }
        return false;
    }

    template< typename T, int nType>
    bool    FixMemAllocer<T, nType>::Init( UINT nItemNum )
    {
        UINT nChunkNum = ( (_wItemSize + sizeof(FixBlock)) * nItemNum ) / ( 64 * 1024 ) + 1;
        for( int i = 0; i< nChunkNum; ++i )
        {
            AppendChunk();
        }
    }

    template< typename T, int nType>
    void    FixMemAllocer<T, nType>::AppendChunk( UINT nSize )
    {
        void *pData = NULL;
        try
        {
            pData = new( sizeof(FixChunk)+nSize );
            ::ZeroMemory( pData, sizeof(FixChunk)+nSize );
            FixChunk* pNewChunk = reinterpret_cast<FixChunk*>( pData );
            pNewChunk->InitChunk( nSize );
            if ( _pFirstChunk )
            {
                FixChunk* pTempChunk = _pFirstChunk;
                while( pTempChunk->pChunkNext != NULL )
                {
                    pTempChunk = pTempChunk->pChunkNext;
                }
                pTempChunk->pChunkNext = pNewChunk;
            }
            else
            {
                _pFirstChunk = pNewChunk;
            }
        }
        catch (exception * e)
        {
        }
    }

    template< typename T, int nType>
    typename FixMemAllocer<T, nType>::FixChunk* FixMemAllocer<T, nType>::GetBlockPtr( T* pItem )
    {
        bool bFind = false;
        UINT nItem = *(&pItem);
        FixChunk* pTmpChunk = _pFirstChunk;
        while ( pTmpChunk != NULL )
        {
            if ( ( nItem > *(&pTmpChunk) ) &&
                ( nItem < *(&pTmpChunk) + pTmpChunk->wByteSize ) )
            {
                bFind = true;
                break;
            }
            pTmpChunk = pTmpChunk->pChunkNext;
        }
        if ( bFind )
        {
            if ( (*&pItem - sizeof(FixBlock) - (*&pTmpChunk + sizeof(FixChunk)) ) % _wItemSize == 0 )
            {
                return reinterpret_cast<FixChunk*>(pItem - sizeof(FixBlock));
            }
        }
        return NULL;
    }


}