#pragma once
#include "lua-5.2.2/src/lua.hpp"
#include "lock.h"

/*******************************************************************************
 约定:
 提供给Lua脚本调用的函数，以L_开头，如L_GetPlayerInfo
 Lua文件里面提供给C调用的函数，以C_开头，如C_PlayerLevelUp
*******************************************************************************/

namespace LibCore
{
    class  luaParam
    {
    public:

        friend class LuaScriptBase;

        luaParam();
        explicit luaParam(bool bValue);
        explicit luaParam(ptrdiff_t nValue);
        explicit luaParam(lua_CFunction cfun);
        explicit luaParam(double dValue);
        explicit luaParam(const char* lpszValue);
        explicit luaParam(void* p);
        

       ~luaParam();

       luaParam(const luaParam& param);
       void operator = (const luaParam& param);

       inline bool isNil()      const   { return eType == type_NIL; }
       inline bool isInt()      const   { return eType == type_INT; }
       inline bool IsBool()     const   { return eType == type_BOOL; }
       inline bool isString()   const   { return eType == type_STRING; }
       inline bool isDouble()   const   { return eType == type_DOUBLE; }
       inline bool isCFunction()const   { return eType == type_CFUNCTION; }
       inline bool isUserData() const   { return eType == type_LIGHTUSERDATA; }

       operator ptrdiff_t()     const   { return _u.intValue; }
       operator bool()          const   { return _u.boolValue; }
       operator char*()         const   { return _u.lpBuffer; }
       operator double()        const   { return _u.doubleValue; }
       operator lua_CFunction() const   { return _u.cFunc; }
       operator void*()         const   { return _u.p; }

    private:

        enum
        {
            type_INT,
            type_NIL,
            type_BOOL,
            type_STRING,
            type_DOUBLE,
            type_CFUNCTION,
            type_LIGHTUSERDATA,
        }eType;

        union
        {
            bool            boolValue;
            ptrdiff_t       intValue;
            double          doubleValue;
            char*           lpBuffer;
            void*           p;
            lua_CFunction   cFunc;
        }_u;

    };

    struct  LuaFunction
    {
        friend class LuaScriptBase;
        LuaFunction& operator [](const luaParam& param);

        void clear();

    private:
        vector<luaParam> vecParam;
        vector<luaParam> vecRet;
    };

    class  LuaScriptBase
    {
    public:
        LuaScriptBase();
       virtual ~LuaScriptBase();

       bool                 Initialize(const char* logfilename);
       void                 Release();
       
       bool                 DoFile(const char* filepath);        // 调用一个Lua文件;
       bool                 DoString(const char* lpstring);
       bool                 DoBuffer(const char* lpBuffer, size_t size);

       // 调用一个Lua函数;
       bool                 CallFunction(const char* funcName, LuaFunction& funObj, int expectReturnCount = 0);

       // 注册一个C函数，供LUA中调用;
       void                 RegisterFunction(const char* funcName, lua_CFunction cFun);
      
       inline lua_State*    get_lua_State();

    protected:
        virtual bool        OnInitialize(){return true;}
        virtual void        OnRelease(){}

    protected:
        void                _writelogfile(const char* err);

    protected:
        lua_State*          m_luaState;

    protected:
        lock                m_lock; // 线程吉祥锁;

        ofstream            m_logfile;  // 日志文件记录器;

    };
}

