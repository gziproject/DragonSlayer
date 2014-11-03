#include "Role.h"
#include "ArmatureLoader.h"

CRole::CRole(void)
{
    m_fB2Width = 2.2f;
    m_fB2Height = 3.0f;
}

CRole::~CRole(void)
{
}

CGameObject* CRole::create(int rid)
{
    CGameObject *armature = new CRole();
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

int CRole::GetRoleType()
{
    return ROLETYPE_HERO;
}

void CRole::ThrowAxe()
{
    
}
