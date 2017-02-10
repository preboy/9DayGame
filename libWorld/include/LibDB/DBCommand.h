#pragma once
namespace LibDB
{
    // 主要执行返回数据集SQL命令;
    // 执行存储过程部分暂不考虑;
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
