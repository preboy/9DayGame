#pragma once

// DB�洢�Ľ�ɫ������Ϣ
struct player_info_db
{
    int nLevel;
};

// ������ó������ݣ����統ǰ���HP
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


// GS ע�ᵽ AS�Ľṹ;
struct msg_gs_reg2_as_c
{
    int     GSID;               // ע��ID����ϷΨһID;
    int     regRet;             // ������Ϣ;
    char    szGSName[12];       // ��Ϸ����������;

    msg_gs_reg2_as_c()
    {
        memset(this, 0, sizeof(msg_gs_reg2_as_c));
    }
};

typedef msg_gs_reg2_as_c msg_gs_reg2_as_s;

// db ע�ᵽ gS�Ľṹ;
struct msg_db_reg2_gs_c
{
    int     DBID;               // ע��ID����ϷΨһID;
    int     regRet;             // ������Ϣ;
    char    szDBName[12];       // ��Ϸ����������;

    msg_db_reg2_gs_c()
    {
        memset(this, 0, sizeof(msg_db_reg2_gs_c));
    }
};

typedef msg_db_reg2_gs_c msg_db_reg2_gs_s;

// lsע�ᵽdb�Ľṹ;
struct msg_ls_reg2_db_c
{
    int     LSID;               // ע��ID����ϷΨһID;
    int     regRet;             // ������Ϣ;
    char    szLSName[12];       // ��Ϸ����������;

    msg_ls_reg2_db_c()
    {
        memset(this, 0, sizeof(msg_ls_reg2_db_c));
    }
};

typedef msg_ls_reg2_db_c msg_ls_reg2_db_s;

// ֪ͨGS���ӳɹ�����;
struct msg_as_accept_gs_sc
{
    int nserved;
};

// ֪ͨDB���ӳɹ�����;
struct msg_gs_accept_db_sc
{
    int nserved;
};

// ֪ͨLS���ӳɹ�����;
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
