#include "GameObject.h"
#include "DGameDef.h"
#include "ArmatureLoader.h"

using namespace std;
USING_NS_CC_EXT;
USING_NS_CC;

CGameObject::CGameObject(void):
    m_fB2Width(1.0f),
    m_fB2Height(1.0f),
    m_fBlood(100.0f),
    m_pB2body(NULL)
{
}

CGameObject::~CGameObject(void)
{
}

CGameObject* CGameObject::create(int rid)
{
    CGameObject *armature = new CGameObject();
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


void CGameObject::PlayAction(const char *szActionName)
{
    // 提前做判断, 不让程序奔溃
    if (getAnimation()->getAnimationData()->getMovement(szActionName) != NULL)
    {
        getAnimation()->play(szActionName);
    }
}

float CGameObject::GetB2Width()
{
    return m_fB2Width;
}

float CGameObject::GetB2Height()
{
    return m_fB2Height;
}

void CGameObject::onEnter()
{
    CCArmature::onEnter();
    setScale(0.5);
}

void CGameObject::onExit()
{
    CCArmature::onExit();
}

void CGameObject::update(float dt)
{
    CCArmature::update(dt);

    if (m_pB2body!= NULL)
    {
        b2Vec2 vPos = m_pB2body->GetPosition();
        CCLog("box2d obj pos: x=%f, y=%f", vPos.x, vPos.y);
        setPosition(vPos.x* PTM_RATIO,  vPos.y * PTM_RATIO);

        CCLog("player obj pos: x=%f, y=%f", getPositionX(), getPositionY());
        CCLog("player obj anchor: x=%f, y=%f", getAnchorPoint().x, getAnchorPoint().y);
        CCLog("player obj w=%f, h=%f", GetB2Width(), GetB2Height());
    }
}
