#pragma once

// DB存储的角色基本信息
struct player_info_db
{
    int nLevel;
};

// 经计算得出的数据，比如当前最大HP
struct player_info_calc
{
    int maxHP;
};

struct msg_test_ld_c
{
    int nAge;
    char szName[12];
    int xtimex;
};

typedef msg_test_ld_c msg_test_dl_s;


// GS 注册到 AS的结构;
struct msg_gs_reg2_as_c
{
    int     GSID;               // 注册ID，游戏唯一ID;
    int     regRet;             // 返回消息;
    char    szGSName[12];       // 游戏服务器名称;

    msg_gs_reg2_as_c()
    {
        memset(this, 0, sizeof(msg_gs_reg2_as_c));
    }
};

typedef msg_gs_reg2_as_c msg_gs_reg2_as_s;

// db 注册到 gS的结构;
struct msg_db_reg2_gs_c
{
    int     DBID;               // 注册ID，游戏唯一ID;
    int     regRet;             // 返回消息;
    char    szDBName[12];       // 游戏服务器名称;

    msg_db_reg2_gs_c()
    {
        memset(this, 0, sizeof(msg_db_reg2_gs_c));
    }
};

typedef msg_db_reg2_gs_c msg_db_reg2_gs_s;

// ls注册到db的结构;
struct msg_ls_reg2_db_c
{
    int     LSID;               // 注册ID，游戏唯一ID;
    int     regRet;             // 返回消息;
    char    szLSName[12];       // 游戏服务器名称;

    msg_ls_reg2_db_c()
    {
        memset(this, 0, sizeof(msg_ls_reg2_db_c));
    }
};

typedef msg_ls_reg2_db_c msg_ls_reg2_db_s;

// 通知GS连接成功建立;
struct msg_as_accept_gs_sc
{
    int nserved;
};

// 通知DB连接成功建立;
struct msg_gs_accept_db_sc
{
    int nserved;
};

// 通知LS连接成功建立;
struct msg_db_accept_ls_sc
{
    int nserved;
};

struct msg_as_test_robot_sc
{
	int				a;
	char			name[32];
	unsigned int	b;
	char			szBuff[128];
};

struct msg_as_test_robot_sc_1
{
	int				a;
	char			name[32];
	unsigned int	b;
	char			szBuff[128];
};
