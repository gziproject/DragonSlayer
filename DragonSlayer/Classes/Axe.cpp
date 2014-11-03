#include "Axe.h"
#include "DGameDef.h"
#include "Monster.h"

CAxe::CAxe(void)
{
    m_fB2Radius = 1.0f;
    m_fPower = 100.0f;
}

CAxe::~CAxe(void)
{
}

CPhysicsObject* CAxe::create(int rid)
{
    CPhysicsObject *pObj = new CAxe;
    if (pObj &&  pObj->init())
    {
        pObj->autorelease();
        return pObj;
    }

    CC_SAFE_RELEASE(pObj);
    return NULL;
}

int CAxe::GetRoleType()
{
    return ROLETYPE_AXE;
}

void CAxe::Attack(CGameObject *pDragon)
{
    if (NULL == pDragon)
        return;

    CMonster *pMonster = dynamic_cast<CMonster*>(pDragon);
    if (pMonster != NULL)
    {
        pMonster->Injure(m_fPower);
    }
}