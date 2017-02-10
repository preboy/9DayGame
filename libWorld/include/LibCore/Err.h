#pragma once

namespace LibCore
{ 
     class  Err
     {
     public:
        Err();
        Err(DWORD dwErrCode);
       ~Err();

        LPWSTR          get_message( DWORD dwErrCode = 0 );

        DWORD           get_last_code();
        LPWSTR          get_last_message();

     private:
        void            _free();

    private:
        LPWSTR          m_lpstr;
        DWORD           m_dwErr;
     };

}