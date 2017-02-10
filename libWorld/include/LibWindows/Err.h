#pragma once

namespace LibWindows
{ 

     class Err
     {
     public:
        Err() : m_lpstr( nullptr )
        {
        }

        Err(DWORD dwErrCode) : m_lpstr( nullptr )
        {
            m_dwErr = dwErrCode;
            get( dwErrCode );
        }

        ~Err()
        {
            _free();
        }

        void get( DWORD dwErrCode = 0 )
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
        }


        inline LPWSTR get_string()
        {
            return m_lpstr;
        }

        inline DWORD get_err_code()
        {
            return m_dwErr;
        }

     private:
        void _free()
        {
            if ( m_lpstr )
            {
                LocalFree (m_lpstr);
                m_lpstr = nullptr;
            }
        }

    private:
        LPWSTR  m_lpstr;
        DWORD   m_dwErr;
     };

}