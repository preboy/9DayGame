#include "stdafx.h"
#include "LibDB/DBRecordSet.h"

namespace LibDB
{



    DBRecordSet::DBRecordSet()
    {
        m_pRecordset.CreateInstance(__uuidof(Recordset));
    }

    DBRecordSet::DBRecordSet(const DBRecordSet&)
    {    
        m_pRecordset.CreateInstance(__uuidof(Recordset));
    }

    DBRecordSet::DBRecordSet(const _RecordsetPtr &recordset)
    {
        m_pRecordset = recordset;
    }

    DBRecordSet& DBRecordSet::operator = (const DBRecordSet &recordset)
    {
        m_pRecordset = recordset.GetRecordsetPtr();
        return *this;
    }

    DBRecordSet::~DBRecordSet()
    {
    }

    const char* DBRecordSet::get_string(const char* szField)
    {
        memset(m_szBuff, 0x0, E_MAX_CHAR);
        try
        {
            _variant_t tmp = m_pRecordset->GetCollect(szField);
            if ( tmp.vt == VT_NULL)                
            {
                return m_szBuff;
            }

            char* p = _com_util::ConvertBSTRToString(tmp.bstrVal);
            memcpy_s(m_szBuff, E_MAX_CHAR, p, strlen(p) );
            delete[] p;
        }
        catch (_com_error &e)
        {
            cout<<"Error Msg:%s."<<e.ErrorMessage()<<endl;      
            return nullptr;
        }
        return m_szBuff;
    }

    const int DBRecordSet::get_int(const char* szField)
    {
        int nValue = 0;
        try
        {
            nValue = (m_pRecordset->Fields->GetItem(_variant_t(szField))->Value).intVal;                
        }
        catch (_com_error &e)
        {
            cout<<"Error Msg:%s."<<e.ErrorMessage()<<endl;      
            return -1;
        }
        return nValue;
    }

    const unsigned int DBRecordSet::get_uint(const char* szField)
    {
        unsigned int nValue;
        try
        {
            nValue = (m_pRecordset->Fields->GetItem(_variant_t(szField))->Value).uintVal;                
        }
        catch (_com_error &e)
        {
            cout<<"Error Msg:%s."<<e.ErrorMessage()<<endl;      
            return -1;
        }
        return nValue;
    }

    bool DBRecordSet::MoveNext()
    {
        try
        {
            return SUCCEEDED(m_pRecordset->MoveNext());
        }
        catch (_com_error &e)
        {
            cout<<"Error Msg:%s."<<e.ErrorMessage()<<endl;      
            return false;
        }
        return false;
    }

    bool DBRecordSet::MoveFirst()
    {
        try
        {
            return SUCCEEDED(m_pRecordset->MoveFirst());
        }
        catch (_com_error &e)
        {
            cout<<"Error Msg:%s."<<e.ErrorMessage()<<endl;      
            return false;
        }
        return false;
    }

    bool DBRecordSet::IsEmpty()
    {
        try
        {
            if ( m_pRecordset == NULL )
            {
                return true;
            }
        }
        catch(_com_error&e)
        {
            cout<<"Error Msg:%s."<<e.ErrorMessage()<<endl;      
            return false;
        }
        return false;
    }

    bool DBRecordSet::IsEOF()
    {
        if ( m_pRecordset->adoEOF ) return true;
        return false;
    }
}