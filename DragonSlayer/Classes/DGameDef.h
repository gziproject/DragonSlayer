#ifndef __DGAMEDEF_H__
#define __DGAMEDEF_H__

#define ACTIONNAME_MOVE             "Move"
#define ACTIONNAME_ATTACK           "Attack"
#define ACTIONNAME_DIE              "Die"
#define ACTIONNAME_INJURE           "Injure"

#define PTM_RATIO                   32

#define MSG_ROLEACOMPLETE           "MsgRoleAComplete"              //玩家攻击动作完成
#define MSG_UICHANGEAXE             "MsgChangeAxe"                  //玩家点击UI界面, 切换了斧子

enum ERoleType
{
    ROLETYPE_NONE = 0,                   //什么也不是
    ROLETYPE_HERO,                       //英雄角色
    ROLETYPE_MONSTER,                    //怪物
    ROLETYPE_AXE,                        //子弹
};

enum ERoleID
{
    ROLEID_NONE      = 0,                //什么也不是
    ROLEID_HERO      = 1000,             //英雄角色

    ROLEID_MONSTER   = 2000,             //怪物角色
    ROLEID_DRAGON    = 2001,             //怪物龙
    
    ROLEID_AXE       = 3000,             //子弹
    ROLEID_NORMAXE   = 3001,             //普通斧子
    ROLEID_FIREAXE   = 3002,             //火斧子
    ROLEID_ICEAXE    = 3003,             //冰斧子
    ROLEID_BANEAXE   = 3004,             //毒斧子
    ROLEID_WINDAXE   = 3005,             //风斧子
    ROLEID_MONSHIT   = 3006,             //怪物拉屎!
};

#endif //__DGAMEDEF_H__
