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
        // ��������ײ, �����Ƿ��й���, ���������, �Դ����ж��Ƿ���ӹ���

    }
}
