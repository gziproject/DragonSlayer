#include "Axe.h"
#include "DGameDef.h"
#include "Monster.h"

USING_NS_CC;

CAxe::CAxe(void)
{
    m_fB2Radius = 1.5f;
    m_fPower = 100.0f;
    m_fExtraPower = 0.0f;
}

CAxe::~CAxe(void)
{
}

CPhysicsObject* CAxe::create(int rid)
{
    CPhysicsObject *pObj = new CAxe;
    if (pObj &&  pObj->init())
    {
        //pObj->autorelease();
        pObj->setAnchorPoint(ccp(0.5f, 0.5f));
        return pObj;
    }

    CC_SAFE_RELEASE(pObj);
    return NULL;
}

int CAxe::GetRoleType()
{
    return ROLETYPE_AXE;
}

void CAxe::InitWithRid(int rid)
{
    SetRoleID(rid);
    m_fPower = 100;
    switch(rid)
    {
    case ROLEID_NORMAXE:
        break;
    case ROLEID_FIREAXE:
        break;
    case ROLEID_ICEAXE:
        break;
    case ROLEID_BANEAXE:
        break;
    case ROLEID_WINDAXE:
        break;
    }
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

void CAxe::RemoveSelf()
{
    removeFromParentAndCleanup(true);
}

void CAxe::onEnter()
{
    CPhysicsObject::onEnter();
    //setScale(0.5f);
}