#include "stdafx.h"
#include "LibDB/MySQL_Proxy.h"

extern DWORD g_String2DWORD(const char* pString);

namespace LibDB
{
    //////////////////////////////////////////////////////////////////////////
    MySQL_Proxy::QueryResult::QueryResult()
    {
        m_pResult = nullptr;
    }

    MySQL_Proxy::QueryResult::~QueryResult()
    {
        if(m_pResult)
        {
            mysql_free_result(m_pResult);
            m_pResult = nullptr;
        }
    }

    bool MySQL_Proxy::QueryResult::GetRecord()
    {
        if(m_pResult)
        {
            m_record = mysql_fetch_row(m_pResult);
            return (m_record ? true : false);
        }

        return false;
    }

    void MySQL_Proxy::QueryResult::_Init(MYSQL_RES* pResult)
    {
        m_pResult = pResult;
        if(m_pResult)
        {
            m_fields = mysql_num_fields(m_pResult);

            UINT i = 0;
            MYSQL_FIELD* pField = nullptr;

            while ( i < m_fields )
            {
                pField = mysql_fetch_field(m_pResult);
                {
                    m_mapIndex[pField->name] = i++;
                }
            }
        }
    }

    int MySQL_Proxy::QueryResult::_GetIndexByName(const char* pFieldsname)
    {
        if(m_mapIndex.find(pFieldsname) == m_mapIndex.end())
        {
            return -1;
        }

        return m_mapIndex[pFieldsname];
    }

    UINT MySQL_Proxy::QueryResult::GetRecordCount()
    {
        return m_fields;
    }

    const char* MySQL_Proxy::QueryResult::GetField(int nIndex)
    {
        if(nIndex < 0 || (UINT)nIndex >= m_fields)
            return nullptr;

        return m_record[nIndex];
    }

    bool MySQL_Proxy::QueryResult::GetBlob(const char* pFieldsname, void** pAddr, DWORD* pLen)
    {
        return true;
    }

    bool MySQL_Proxy::QueryResult::GetDWORD(const char* pFieldsname, DWORD* pVal)
    {
        const char* pValue = GetField(_GetIndexByName(pFieldsname));
        if(pValue)
        {
            *pVal = g_String2DWORD(pValue);
            return true;
        }

        return false;
    }

    const char* MySQL_Proxy::QueryResult::GetString(const char* pFieldsname)
    {
        return GetField(_GetIndexByName(pFieldsname));
    }


    MySQL_Proxy::MySQL_Proxy()
    {
        m_pModule    = nullptr;
        m_pConn      = nullptr;
    }

    MySQL_Proxy::~MySQL_Proxy()
    {
    }


    bool MySQL_Proxy::MySQL_Init()
    {
        if(mysql_library_init(0, nullptr, nullptr))
        {
            return false;
        }

        m_pModule = mysql_init(nullptr);
        if(!m_pModule)
        {
            return false;
        }

        return true;
    }

    void MySQL_Proxy::MySQL_Release()
    {
        mysql_close(m_pModule);
        mysql_library_end();
    }

    bool MySQL_Proxy::MySQL_Connect(const char* host, const char* user, const char* passwd, const char* db, 
        unsigned int port, const char *unix_socket, unsigned long client_flag)
    {
        m_pConn = mysql_real_connect(m_pModule, host, user, passwd, db, port, unix_socket, client_flag);
        if(!m_pConn)
        {
            const char* strError = mysql_error(m_pModule);
            return false;
        }

        mysql_query(m_pConn, "SET AUTOCOMMIT=0");
        return true;
    }

    void MySQL_Proxy::MySQL_DisConnect()
    {
        // mysql_shutdown(m_pConn, SHUTDOWN_DEFAULT);
    }

    bool MySQL_Proxy::MySQL_ExecuteQuery(const char* query_string, QueryResult& qr)
    {
        assert(query_string);
        if(mysql_query(m_pConn, query_string))
        {
            return false;
        }

        MYSQL_RES*  results = nullptr;

        if(!(results = mysql_store_result(m_pConn)))
        {
            if(mysql_field_count(m_pConn) != 0)
            {
                mysql_error(m_pConn);
                return false;
            }
        }

        qr._Init(results);

        return true;
    }

    bool MySQL_Proxy::MySQL_ExecuteCommand(const char* query_string)
    {
        if(mysql_query(m_pConn, query_string))
        {
            return false;
        }

        MYSQL_RES*  results;
        if(!(results = mysql_store_result(m_pConn)))
        {
            if(mysql_field_count(m_pConn) == 0)
            {
                // 查询未返回数据（例如，它是INSERT、UPDATE或DELETE）;
                my_ulonglong num_rows = mysql_affected_rows(m_pConn);
                return true;
            }
            else
            {
                // 出现了malloc()故障（例如，如果结果集过大）。
                // 无法读取数据（在连接上出现了错误）。
                mysql_error(m_pConn);
                return false;
            }
        }

        return true;
    }

    void MySQL_Proxy::MySQL_BeginTrans()
    {
        mysql_query(m_pConn, "SET AUTOCOMMIT=0");
        mysql_query(m_pConn, "BEGIN");
    }

    void MySQL_Proxy::MySQL_RollTrans()
    {
        mysql_query(m_pConn, "ROOLBACK");
        mysql_query(m_pConn, "SET AUTOCOMMIT=1");
    }

    void MySQL_Proxy::MySQL_CommitTrans()
    {
        mysql_query(m_pConn, "COMMIT");
        mysql_query(m_pConn, "SET AUTOCOMMIT=1");
    }

}