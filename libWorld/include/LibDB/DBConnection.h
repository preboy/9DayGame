#pragma once

using namespace ADODB;  

namespace LibDB
{
    class  DBConnection
    {
    public:
        DBConnection();
       ~DBConnection();

    public:

        _ConnectionPtr& GetConnection() {return m_pConnection;}

        bool ConnectSQLServer(  const char* host, const char* dbname, 
                                const char* user, const char* pass,
                                long  lOptions = adConnectUnspecified);
        void DisConnect();

        // 执行非查询类SQL命令;
        bool Execute(const char* szSQL, long lOptions = adCmdText);

        // 以事务方式执行非查询类SQL命令;
        bool Execute_transaction(const char* szSQL, long lOptions = adCmdText);

    private:

        bool Open(const char* lpszConnect, long lOptions);

        bool IsOpen();

        bool SetConnectTimeOut(long lTime = 5);

        void Release();

    private:
        _ConnectionPtr    m_pConnection;
    };

}
