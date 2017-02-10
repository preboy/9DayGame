#include "stdafx.h"
#include "LibDB/DBConnection.h"

namespace LibDB
{



    DBConnection::DBConnection()
    {
        m_pConnection.CreateInstance("ADODB.Connection");  
        SetConnectTimeOut();
    }

    DBConnection::~DBConnection()
    {
        Release();
    }

    bool DBConnection::Open(const char* lpszConnect, long lOptions)
    {
        if ( IsOpen() || !lpszConnect || !strlen(lpszConnect) )
        {
            return false;
        }

        try
        {
            m_pConnection->Open(lpszConnect, "", "", lOptions);
        }
        catch (_com_error e)
        {
            cout<<"Warning: 连接数据库发生异常. 错误信息:"<<e.ErrorMessage()<<endl;
            return false;
        } 
        catch (...)
        {
            cout<<"Warning: 连接数据库时发生未知错误."<<endl;
            return false;
        }
        return true;
    }

    bool DBConnection::ConnectSQLServer(const char* host, const char* dbname, const char* user, const char* pass, long lOptions)
    {
        char szBuffer[256] = { 0 };

        sprintf_s<256>( szBuffer, 
            "Provider=SQLNCLI10;Server=%s;Database=%s;Uid=%s;Pwd=%s;", 
            host, dbname, user, pass );

        return Open(szBuffer, lOptions);
    }

    void DBConnection::DisConnect()
    {
        try
        {
            if (m_pConnection != nullptr && IsOpen()) 
            {
                m_pConnection->Close();
            }
        }
        catch (_com_error e)
        {
            cout<<"Warning: 关闭数据库发生异常. 错误信息:"<<e.ErrorMessage()<<endl;
        } 
    }

    void DBConnection::Release()
    {
        if (IsOpen()) 
        {
            DisConnect();
        }
        m_pConnection.Release();
    }


    bool DBConnection::Execute(const char* szSQL, long lOptions)
    {
        try
        {
            m_pConnection->Execute(_bstr_t(szSQL), NULL, lOptions);
        }
        catch (_com_error& e)
        {
            cout<<"Warning: Execute 方法发生异常. 错误信息:"<<e.ErrorMessage()<<endl;
            return false;
        }
        return true;
    }

    bool DBConnection::Execute_transaction(const char* szSQL, long lOptions)
    {
        try
        {
            m_pConnection->BeginTrans();
            m_pConnection->Execute(_bstr_t(szSQL), NULL, lOptions);
            m_pConnection->CommitTrans();
        }
        catch (_com_error& e)
        {
            m_pConnection->RollbackTrans();
            cout<<"Warning: Execute_transaction 方法发生异常. 错误信息:"<<e.ErrorMessage()<<endl;
            return false;
        }
        return true;
    }

    bool DBConnection::SetConnectTimeOut(long lTime)
    {
        try
        {
            m_pConnection->PutConnectionTimeout(lTime);
        }
        catch (_com_error e)
        {
            cout<<"Warning: SetConnectTimeOut 方法发生异常. 错误信息:"<<e.ErrorMessage()<<endl;
            return false;
        } 
        return true;
    }

    bool DBConnection::IsOpen()
    {
        try
        {
            return (m_pConnection != nullptr && (m_pConnection->State & adStateOpen));
        }
        catch (_com_error e)
        {
            cout<<"Warning: IsOpen 方法发生异常. 错误信息:"<<e.ErrorMessage()<<endl;
            return false;
        }
        return false;
    }
}