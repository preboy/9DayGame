#pragma once
// �ṩ�����ݿ⽻����ʵ�ʽӿ�;

#define __LCC__
#include "MySQL/include/mysql.h"

namespace LibDB
{
    class  MySQL_Proxy
    {
    public:
        // ִ��Select֮�󷵻صĲ�ѯ;
        class QueryResult
        {
        public:
            explicit QueryResult();
           ~QueryResult();

        public:
           // ��ȡ���;
           bool         GetRecord();

           // ��ȡ��ѯ��Ϣ;
           UINT         GetRecordCount();

           // ��ȡ�ֶ�����;
           const char*  GetField(int nIndex);

           bool         GetBlob(const char* pFieldsname, void** pAddr, DWORD* pLen);
           bool         GetDWORD(const char* pFieldsname, DWORD* pVal);
           const char*  GetString(const char* pFieldsname);

        private:
            friend class MySQL_Proxy;
            void        _Init(MYSQL_RES* pResult);

            // ��ȡ�ֶ�����, ʧ��ʱ����-1;
            int         _GetIndexByName(const char* pFieldsname);

        private:
            MYSQL_RES*              m_pResult;
            map<string, UINT>       m_mapIndex; // �������ֶ�����ӳ���;
            MYSQL_ROW               m_record;
            UINT                    m_fields;   // ����;
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

        // ֱ�ӷ���ʽ��ѯ;
        bool MySQL_ExecuteQuery(const char* query_string, QueryResult& qr);

        // �ص�ʽ��ѯ;
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
                    // ��ѯδ�������ݣ����磬����INSERT��UPDATE��DELETE��;
                    my_ulonglong num_rows = mysql_affected_rows(m_pConn);
                    return true;
                }
                else
                {
                    // ������malloc()���ϣ����磬�����������󣩡�
                    // �޷���ȡ���ݣ��������ϳ����˴��󣩡�
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

        // ִ�з�select�����,ԭ�Ӳ���;
        bool        MySQL_ExecuteCommand(const char* query_string);

        // �������;
        void        MySQL_BeginTrans();
        void        MySQL_RollTrans();
        void 	    MySQL_CommitTrans();
        
    private:

        MYSQL*  m_pModule;
        MYSQL*  m_pConn;
    };
}

/*
    �����ƵĴ���
    ��������ת����varant
    �ֶΰ�;
*/