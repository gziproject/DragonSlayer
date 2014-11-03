/************************************************************************/
/* 怪物管理器, 进入游戏时, 用于初始化怪物, 配置怪物, 以及游戏结束时清理怪物信息      */
/*                                                                       */
/************************************************************************/

#ifndef __MONSTER_MANAGER_H__
#define __MONSTER_MANAGER_H__

#include "cocos2d.h"
#include <list>

class CMonsterManager
{
public:
    CMonsterManager(void);
    ~CMonsterManager(void);

public:

    // 进入游戏时, 重置怪物信息
    bool InitMonsterMrg();

    // 结束游戏, 结算怪物信息
    bool UninitMonsterMrg();

    // 设置游戏场景
    void SetMonsterScene(cocos2d::CCLayer *pLayer);

    // 轮询管理器
    void UpdateMonsterMrg(float dt);
    
private:
    
    cocos2d::CCLayer                     *m_GameScene;       //游戏场景
    std::list<cocos2d::CCObject *>       m_MonsterList;      //怪物列表
};

#endif //__MONSTER_MANAGER_H__