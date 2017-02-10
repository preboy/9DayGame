#pragma once
namespace LibDB
{
    // ��Ҫִ�з������ݼ�SQL����;
    // ִ�д洢���̲����ݲ�����;
    class  DBCommand
    {
    public:
        DBCommand();
        DBCommand( const _ConnectionPtr pAdoConnection, const char* szCommandText = NULL, 
                   CommandTypeEnum CommandType = adCmdStoredProc );
      
       ~DBCommand();

       bool             SetConnection(const _ConnectionPtr pConnect);
       bool             SetCommandType(CommandTypeEnum CommandType);
       bool             SetCommandText(const char* lpstrCommand);

       bool             SetCommandTimeOut(long lTime);
       _CommandPtr      GetCommand() {return m_pCommand;}
       void             Release();

       _RecordsetPtr    Execute(long Options = adCmdText);

    private:
        _CommandPtr     m_pCommand;
    };

}
