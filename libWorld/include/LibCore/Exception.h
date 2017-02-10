#pragma once
/************************************************************
*
*    author:        ÕÅ³¯¹ú
*    E-mail:        preboy@126.com
*    Date:          2011-02-10
*
************************************************************/

namespace LibCore
{
    class  Exception : public exception
    {
    public:
        Exception(const char *_Message);
        Exception(const char *_Message, int);
       ~Exception(void);

    private:
        unsigned int    _errCode;
    };
}


