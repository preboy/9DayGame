#include "stdafx.h"
#include "LibDB/DBCommand.h"

namespace LibDB
{
    DBCommand::DBCommand()
    {
        m_pCommand.CreateInstance("ADODB.Command");
    }

    DBCommand::DBCommand( const _ConnectionPtr pAdoConnection, const char* szCommandText, CommandTypeEnum CommandType )
    {
        m_pCommand.CreateInstance("ADODB.Command");

        SetConnection(pAdoConnection);
        SetCommandText(szCommandText);
        SetCommandType(CommandType);
    }

    DBCommand::~DBCommand()
    {
        Release();
    }

    void DBCommand::Release()
    {
        try
        {
            m_pCommand.Release();
        }
        catch (_com_error e)
        {
            cout<<"Warning: Release方法发生异常. 错误信息:"<<e.ErrorMessage()<<endl;
        } 
    }

    _RecordsetPtr DBCommand::Execute(long Options)
    {
        try
        {
            return m_pCommand->Execute(nullptr, nullptr, Options);
        }
        catch (_com_error e)
        {
            cout<<"Warning: Execute 方法发生异常. 错误信息:"<<e.ErrorMessage()<<endl;
            return nullptr;
        }
        return nullptr;
    }


    bool DBCommand::SetCommandText(const char* lpstrCommand)
    {
        if ( !m_pCommand || !lpstrCommand || !strlen(lpstrCommand) )
        {
            return false;
        }

        try
        {
            m_pCommand->PutCommandText(_bstr_t(lpstrCommand));
        }
        catch (_com_error e)
        {
            cout<<"Warning: PutCommandText 方法发生异常. 错误信息:"<<e.ErrorMessage()<<endl;
            return false;
        }
        return true;
    }

    bool DBCommand::SetConnection(const _ConnectionPtr pConnect)
    {
        if ( !m_pCommand || !pConnect )
        {
            return false;
        }

        try
        {
            m_pCommand->PutActiveConnection(_variant_t((IDispatch*)pConnect, true));
        }
        catch (_com_error e)
        {

            cout<<"Warning: SetConnection 方法发生异常. 错误信息:"<<e.ErrorMessage()<<endl;
            return false;
        }
        return true;
    }

    bool DBCommand::SetCommandType(CommandTypeEnum CommandType)
    {
        if ( !m_pCommand )
        {
            return false;
        }

        try
        {
            m_pCommand->PutCommandType(CommandType);
        }
        catch (_com_error e)
        {
            cout<<"Warning: PutCommandType 方法发生异常. 错误信息:"<<e.ErrorMessage()<<endl;
            return false;
        } 
        return true;
    }

    bool DBCommand::SetCommandTimeOut(long lTime)
    {
        try
        {
            m_pCommand->PutCommandTimeout(lTime);
        }
        catch (_com_error e)
        {
            cout<<"Warning: SetCommandTimeOut 方法发生异常. 错误信息:"<<e.ErrorMessage()<<endl;
            return false;
        }
        return true;
    }
}