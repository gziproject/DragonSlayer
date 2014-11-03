#include "MonsterManager.h"


CMonsterManager::CMonsterManager(void)
{
}


CMonsterManager::~CMonsterManager(void)
{
}

bool CMonsterManager::InitMonsterMrg()
{
    return true;
}

bool CMonsterManager::UninitMonsterMrg()
{
    return true;
}

void CMonsterManager::SetMonsterScene(cocos2d::CCLayer *pLayer)
{
    m_GameScene = pLayer;
}

void CMonsterManager::UpdateMonsterMrg(float dt)
{
    if (m_GameScene != NULL)
    {
        // 不计算碰撞, 计算是否还有怪物, 怪物的数量, 以此来判断是否添加怪物

    }
}
