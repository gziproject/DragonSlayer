#ifndef __DGAMEDEF_H__
#define __DGAMEDEF_H__

#define ACTIONNAME_MOVE             "Move"
#define ACTIONNAME_ATTACK           "Attack"
#define ACTIONNAME_DIE              "Die"
#define ACTIONNAME_INJURE           "Injure"

#define PTM_RATIO                   62

#define MSG_ROLEACOMPLETE           "MsgRoleAComplete"                        //��ҹ����������
#define MSG_UICHANGEAXE             "MsgChangeAxe"                            //��ҵ��UI����, �л��˸���

static const int COLLIDE_INDEX_OBJECTGROUP =  0x0001;                                //����Ⱥ��
static const int COLLIDE_INDEX_BULLETGROUP =  0x0002;                                //�ӵ�Ⱥ��

static const int COLLIDE_CATEGORY_ROLE =      0x0002;                                //��ɫ����
static const int COLLIDE_MASKBIT_ROLE =       0xFFFF ^ COLLIDE_CATEGORY_ROLE;        //��ɫ��ײ����

static const int COLLIDE_CATEGORY_MONSTER =   0x0004;                                //��������
static const int COLLIDE_MASKBIT_MONSTER =    0xFFFF ^ COLLIDE_CATEGORY_MONSTER;     //������ײ����

// fonts
static const char *szFontAxeCnt = "";

enum ERoleType
{
    ROLETYPE_NONE = 0,                   //ʲôҲ����
    ROLETYPE_HERO,                       //Ӣ�۽�ɫ
    ROLETYPE_MONSTER,                    //����
    ROLETYPE_AXE,                        //�ӵ�
};

enum ERoleID
{
    ROLEID_NONE      = 0,                //ʲôҲ����
    ROLEID_HERO      = 1000,             //Ӣ�۽�ɫ

    ROLEID_MONSTER   = 2000,             //�����ɫ
    ROLEID_DRAGON    = 2001,             //������
    
    ROLEID_AXE       = 3000,             //�ӵ�
    ROLEID_NORMAXE   = 3001,             //��ͨ����
    ROLEID_FIREAXE   = 3002,             //����
    ROLEID_ICEAXE    = 3003,             //������
    ROLEID_BANEAXE   = 3004,             //������
    ROLEID_WINDAXE   = 3005,             //�縫��
    ROLEID_MONSHIT   = 3006,             //������ʺ!
};

#endif //__DGAMEDEF_H__
