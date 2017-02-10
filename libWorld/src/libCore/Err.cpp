#include "stdafx.h"
#include "libCore/Err.h"

namespace LibCore
{ 
    Err::Err() : m_lpstr( nullptr )
    {
    }

    Err::Err(DWORD dwErrCode) : m_lpstr( nullptr )
    {
        m_dwErr = dwErrCode;
        get_message( m_dwErr );
    }

    Err::~Err()
    {
        _free();
    }

    LPWSTR Err::get_message( DWORD dwErrCode )
    {
        _free();

        if ( dwErrCode == 0 )
        {
            dwErrCode = ::GetLastError();
        }

        m_dwErr = dwErrCode;

        DWORD dwErr = FormatMessageW(   FORMAT_MESSAGE_ALLOCATE_BUFFER  | 
            FORMAT_MESSAGE_IGNORE_INSERTS   | 
            FORMAT_MESSAGE_FROM_SYSTEM,
            NULL,
            dwErrCode,
            LANG_NEUTRAL,
            (LPWSTR)&m_lpstr,
            0 ,
            NULL );

        if ( dwErr == 0 )
        {
            m_lpstr = nullptr;
        }

        return m_lpstr;
    }


    LPWSTR Err::get_last_message()
    {
        return m_lpstr;
    }

    DWORD Err::get_last_code()
    {
        return m_dwErr;
    }


    void Err::_free()
    {
        if ( m_lpstr )
        {
            LocalFree(m_lpstr);
            m_lpstr = nullptr;
        }
    }

}