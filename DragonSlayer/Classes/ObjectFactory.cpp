#include "ObjectFactory.h"
#include "Role.h"
#include "Monster.h"
#include "Axe.h"

CObjectFactory::CObjectFactory(void)
{
}


CObjectFactory::~CObjectFactory(void)
{
}

CObjectFactory *CObjectFactory::m_Instance = NULL;
CObjectFactory *CObjectFactory::GetInstance()
{
    if (NULL == m_Instance)
    {
        m_Instance = new CObjectFactory;
    }

    return m_Instance;
}

void CObjectFactory::Destroy()
{
    if (NULL != m_Instance)
    {
        delete m_Instance;
        m_Instance = NULL;
    }
}

CGameObject *CObjectFactory::CreateObject(int rid)
{
    CGameObject *pObj = NULL;
    switch (rid)
    {
    case ROLEID_HERO:
        {
            pObj = CRole::create(rid);   
        }
        break;

    case ROLEID_MONSTER:
    case ROLEID_DRAGON:
        {
            pObj = CMonster::create(rid);
        }
        break;

    default:
        break;
    }

    return pObj;
}


CPhysicsObject *CObjectFactory::CreateAxe(int rid)
{
    CPhysicsObject *pAxe = NULL;
    switch (rid)
    {
    case ROLEID_AXE:
    case  ROLEID_NORMAXE:
    case  ROLEID_FIREAXE:
    case  ROLEID_ICEAXE :
    case  ROLEID_BANEAXE:
    case  ROLEID_WINDAXE:
        {
            pAxe = CAxe::create(rid);   
        }
        break;

    default:
        break;
    }

    return pAxe;
}
