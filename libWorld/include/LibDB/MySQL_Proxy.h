#pragma once
// 提供与数据库交互的实际接口;

#define __LCC__
#include "MySQL/include/mysql.h"

namespace LibDB
{
    class  MySQL_Proxy
    {
    public:
        // 执行Select之后返回的查询;
        class QueryResult
        {
        public:
            explicit QueryResult();
           ~QueryResult();

        public:
           // 获取结果;
           bool         GetRecord();

           // 获取查询信息;
           UINT         GetRecordCount();

           // 获取字段内容;
           const char*  GetField(int nIndex);

           bool         GetBlob(const char* pFieldsname, void** pAddr, DWORD* pLen);
           bool         GetDWORD(const char* pFieldsname, DWORD* pVal);
           const char*  GetString(const char* pFieldsname);

        private:
            friend class MySQL_Proxy;
            void        _Init(MYSQL_RES* pResult);

            // 获取字段索引, 失败时返回-1;
            int         _GetIndexByName(const char* pFieldsname);

        private:
            MYSQL_RES*              m_pResult;
            map<string, UINT>       m_mapIndex; // 索引与字段名的映射表;
            MYSQL_ROW               m_record;
            UINT                    m_fields;   // 列数;
        };

    public:
        MySQL_Proxy();
        ~MySQL_Proxy();

        bool MySQL_Init();
        void MySQL_Release();

        bool MySQL_Connect(
            const char*  host, 
            const char*  user, 
            const char*  passwd, 
            const char*  db, 
            unsigned int port            = 3306, 
            const char*  unix_socket     = nullptr, 
            unsigned long client_flag    = 0);

        void MySQL_DisConnect();

        // 直接返回式查询;
        bool MySQL_ExecuteQuery(const char* query_string, QueryResult& qr);

        // 回调式查询;
        template<class T>
        bool MySQL_ExecuteQuery(const char* query_string, T* pThis, void (T::*fnCallBack)(int numFileds, char** pRecord))
        {
            assert(query_string);
            if(mysql_query(m_pConn, query_string))
            {
                return false;
            }

            int         num_fields;
            MYSQL_ROW   record;
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

            num_fields = mysql_num_fields(results);
            while((record = mysql_fetch_row(results)))
            {
                ((pThis->*fnCallBack))(num_fields, record);
            }

            mysql_free_result(results);
            return true;
        }

        // 执行非select类语句,原子操作;
        bool        MySQL_ExecuteCommand(const char* query_string);

        // 事务相关;
        void        MySQL_BeginTrans();
        void        MySQL_RollTrans();
        void 	    MySQL_CommitTrans();
        
    private:

        MYSQL*  m_pModule;
        MYSQL*  m_pConn;
    };
}

/*
    二进制的处理。
    变量类型转换。varant
    字段绑定;
*/