#include "stdafx.h"
#include "LibCore/LuaScriptBase.h"
#include "LibCore/utility.h"

#pragma warning(disable : 4800)
namespace LibCore
{

    luaParam::luaParam()
    {
        eType = type_NIL;
    }
    luaParam::luaParam(bool bValue)
    {
        eType = type_BOOL;
        _u.boolValue = bValue;
    }
    luaParam::luaParam(ptrdiff_t nValue)
    {
        eType = type_INT;
        _u.intValue = nValue;

    }
    luaParam::luaParam(lua_CFunction cfun)
    {
        eType = type_CFUNCTION;
        _u.cFunc = cfun;
    }
    luaParam::luaParam(double dValue)
    {
        eType = type_DOUBLE;
        _u.doubleValue = dValue;

    }
    luaParam::luaParam(const char* lpszValue)
    {
        eType = type_STRING;
        _u.lpBuffer = nullptr;
        
        if(lpszValue)
        {
            size_t len = strlen(lpszValue);
            _u.lpBuffer = (char*)malloc(len+1);
            _u.lpBuffer[len] = '\0';    
            if(len)
            {
                strcpy_s(_u.lpBuffer, len+1, lpszValue);
            }
        }
    }
    
    luaParam::luaParam(void* p)
    {
        eType = type_LIGHTUSERDATA;
        _u.p = p;
    }

    luaParam::~luaParam()
    {
        if(eType == type_STRING && _u.lpBuffer)
        {
            free(_u.lpBuffer);
            _u.lpBuffer = nullptr;
        }
    }


    luaParam::luaParam(const luaParam& param)
    {
        eType = param.eType;

        if(param.eType == type_STRING)
        {
            if(param._u.lpBuffer)
            {
                size_t len = strlen(param._u.lpBuffer);
                _u.lpBuffer = (char*)malloc(len+1);
                _u.lpBuffer[len] = '\0';
                strcpy_s(_u.lpBuffer, len+1, param._u.lpBuffer);
            }
        }
        else
        {
            _u = param._u;
        }
    }

    void luaParam::operator=(const luaParam& param)
    {
        eType = param.eType;

        if(param.eType == type_STRING)
        {
            if(param._u.lpBuffer)
            {
                size_t len = strlen(param._u.lpBuffer);
                _u.lpBuffer = (char*)malloc(len+1);
                _u.lpBuffer[len] = '\0';
                strcpy_s(_u.lpBuffer, len+1, param._u.lpBuffer);
            }
        }
        else
        {
            _u = param._u;
        }
    }


    //////////////////////////////////////////////////////////////////////////


    LuaFunction& LuaFunction::operator [](const luaParam& param)
    {
        vecParam.push_back(param);
        return *this;
    }

    void LuaFunction::clear()
    {
        vecParam.clear();
        vecRet.clear();
    }

    //////////////////////////////////////////////////////////////////////////

    LuaScriptBase::LuaScriptBase()
    {
        m_luaState = nullptr;
    }


    LuaScriptBase::~LuaScriptBase()
    {
    }

    void LuaScriptBase::RegisterFunction(const char* funcName, lua_CFunction cFun)
    {
        if(m_luaState)
        {
            lua_register(m_luaState, funcName, cFun);
        }
    }

    inline lua_State* LuaScriptBase::get_lua_State()
    {
        return m_luaState;
    }

    bool LuaScriptBase::Initialize(const char* logfilename)
    {
        if(logfilename)
        {
            // 追加的方式写，最好就是当文件大小过大，则删除文件最前面的数据;
            m_logfile.open(logfilename, ios_base::app | ios_base::out);
            if(false == m_logfile.is_open())
            {
                return false;
            }
        }
        
        m_luaState = luaL_newstate();  
        if(m_luaState == nullptr)
        {
            return false;
        }

        luaL_openlibs(m_luaState);

        if(!OnInitialize())
        {
            return false;
        }

        m_logfile<<"---- luaScript日志开启["<<g_TimeToString()<<"] "<<" ----"<<std::endl;

        return true;
    }

    void LuaScriptBase::Release()
    {
        OnRelease();
        lua_close(m_luaState);
        m_luaState = nullptr;
        if(m_logfile.is_open())
        {
            m_logfile.close();
        }
    }

    bool LuaScriptBase::DoFile(const char* filepath)
    {
        lock_critical l(m_lock);

        if(m_luaState == nullptr || filepath == nullptr)
        {
            return false;
        }

        const char* pszErr = NULL;
        int nRet = luaL_dofile(m_luaState, filepath);
        if(nRet)
        {
            pszErr = lua_tostring(m_luaState, -1);
            _writelogfile(pszErr);
            return false;
        }

        return true;
    }


    bool LuaScriptBase::DoString(const char* lpstring)
    {
        lock_critical l(m_lock);

        if(m_luaState == nullptr || lpstring == nullptr)
        {
            return false;
        }

        const char* pszErr = NULL;
        int nRet = luaL_dostring(m_luaState, lpstring);
        if(nRet)
        {
            pszErr = lua_tostring(m_luaState, -1);
            _writelogfile(pszErr);
            return false;
        }

        return true;
    }


    bool LuaScriptBase::DoBuffer(const char* lpBuffer, size_t size)
    {
        // luaL_Buffer()
        return false;
    }


    bool LuaScriptBase::CallFunction(const char* funcName, LuaFunction& funObj, int expectReturnCount)
    {
        lock_critical l(m_lock);

        if(!m_luaState || !funcName)
        {
            return false;
        }

        lua_settop(m_luaState, 0);
        lua_getglobal(m_luaState, funcName);

        for(auto it = funObj.vecParam.begin(); it != funObj.vecParam.end(); it++)
        {
            switch(it->eType)
            {
            case luaParam::type_INT:
                {
                    lua_pushinteger(m_luaState, it->_u.intValue);
                }
                break;

            case luaParam::type_NIL:
                {
                    lua_pushnil(m_luaState);
                }
                break;

            case luaParam::type_BOOL:
                {
                    lua_pushboolean(m_luaState, (int)it->_u.boolValue);
                }
                break;

            case luaParam::type_STRING:
                {
                    lua_pushstring(m_luaState, it->_u.lpBuffer);
                }
                break;

            case luaParam::type_CFUNCTION:
                {
                    lua_pushcfunction(m_luaState, it->_u.cFunc);
                }
                break;

            case luaParam::type_DOUBLE:
                {
                    lua_pushnumber(m_luaState, (lua_Number)it->_u.doubleValue);
                }
                break;

            case luaParam::type_LIGHTUSERDATA:
                {
                    lua_pushlightuserdata(m_luaState, it->_u.p);
                }
                break;

            default:
                {
                    return false;
                    lua_settop(m_luaState, 0);
                }
            }
        }

        size_t nRet = lua_pcall(m_luaState, (int)funObj.vecParam.size(), expectReturnCount, 0);
        if(LUA_OK != nRet)
        {
            const char* pszRet = lua_tostring(m_luaState, 1);
            _writelogfile(pszRet);
            lua_settop(m_luaState, 0);
            return false;
        }

        // 检查参数;
        for(int i=1; i<=expectReturnCount; i++)
        {
            if(lua_isnil(m_luaState, i))
            {
                funObj.vecRet.push_back(luaParam());
            }
            else if(lua_isboolean(m_luaState, i))
            {
                funObj.vecRet.push_back(luaParam((bool)lua_toboolean(m_luaState, i)));
            }
            else if(lua_isnumber(m_luaState, i))
            {
                funObj.vecRet.push_back(luaParam(lua_tointeger(m_luaState, i)));
            }
            else if(lua_isstring(m_luaState, i))
            {
                funObj.vecRet.push_back(luaParam(lua_tostring(m_luaState, i)));
            }
        }

        lua_settop(m_luaState, 0);
        return true;
    }

    void LuaScriptBase::_writelogfile(const char* err)
    {
        if(m_logfile.is_open())
        {
            m_logfile<<"["<<g_TimeToString()<<"] "<<err<<std::endl;
            m_logfile.flush();
        }
    }

}
