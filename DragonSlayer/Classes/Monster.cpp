#include "Monster.h"
#include "ArmatureLoader.h"

USING_NS_CC;

CMonster::CMonster(void)
{
    m_fB2Width = 2.5f;
    m_fB2Height = 1.5f;
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

void CMonster::Injure(int power)
{
    CCTintTo *pTint = CCTintTo::create(0.5f, 128, 128, 128);
    CCSequence *pSeq = CCSequence::create(pTint, pTint->reverse(), NULL);
    runAction(pSeq);

    //PlayAction(ACTIONNAME_INJURE);

    m_fBlood -= power;
    if (m_fBlood <= 0.0f)
    {
        Die();
    }
}

void CMonster::Die()
{
    PlayAction(ACTIONNAME_DIE);
}