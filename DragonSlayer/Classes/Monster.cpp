#include "Monster.h"
#include "ArmatureLoader.h"

USING_NS_CC;

CMonster::CMonster(void)
{
    m_fB2Width = 2.5f;
    m_fB2Height = 1.5f;
    m_bIsTouchGroundRemove = false;
}

CMonster::~CMonster(void)
{
}

CGameObject* CMonster::create(int rid)
{
    CGameObject *armature = new CMonster();
    string name = ArmatureLoader::GetInstance()->GetArmatureName(rid);
    if (name.compare("") != 0)
    {
        if (armature && armature->init(name.c_str()))
        {
            armature->SetRoleID(rid);
            armature->setAnchorPoint(ccp(0.5f, 0.5f));
            armature->autorelease();
            return armature;
        }
    }

    CC_SAFE_DELETE(armature);
    return NULL;
}

int CMonster::GetRoleType()
{
    return ROLETYPE_MONSTER;
}

float CMonster::Injure(int power)
{
    m_fBlood -= power;
    if (m_fBlood <= 0.0f)
    {
        Die();
    }

    return m_fBlood;
}

void CMonster::Die()
{
    PlayAction(ACTIONNAME_DIE);
    b2World *pWorld = m_pB2body->GetWorld();

    b2JointEdge *pJoints = m_pB2body->GetJointList();
    while (pJoints != NULL)
    {
        b2Joint *destroy = pJoints->joint;
        pJoints = pJoints->next;

        pWorld->DestroyJoint(destroy);
    }

    // 设置不与角色, 斧头碰撞
    b2Fixture *pFixture = m_pB2body->GetFixtureList();
    b2Filter filer;
    filer.categoryBits = COLLIDE_CATEGORY_ROLE;
    filer.maskBits = COLLIDE_MASKBIT_ROLE & COLLIDE_MASKBIT_MONSTER;
    pFixture->SetFilterData(filer);

    m_bIsTouchGroundRemove = true;
}