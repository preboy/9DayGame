#pragma once

using namespace ADODB;

namespace LibDB
{
    class  DBRecordSet 
    {
    public:
        DBRecordSet();
       ~DBRecordSet();
        DBRecordSet(const DBRecordSet &recordset);
        DBRecordSet(const _RecordsetPtr &recordset);

    public:
        _RecordsetPtr       GetRecordsetPtr()const{ return m_pRecordset; }
        DBRecordSet&        operator = (const DBRecordSet& recordset);

        const char*         get_string  (const char* szField);
        const int           get_int     (const char* szField);    
        const unsigned int  get_uint    (const char* szField);

        bool                IsEmpty();

        bool                IsEOF();
        bool                MoveNext();
        bool                MoveFirst();

    private:
        enum{ E_MAX_CHAR = 1024, };

        _RecordsetPtr       m_pRecordset;                
        char                m_szBuff[E_MAX_CHAR];
    };
}
