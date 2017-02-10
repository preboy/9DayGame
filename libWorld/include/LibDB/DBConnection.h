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

        // ִ�зǲ�ѯ��SQL����;
        bool Execute(const char* szSQL, long lOptions = adCmdText);

        // ������ʽִ�зǲ�ѯ��SQL����;
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
