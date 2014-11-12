#include "Role.h"
#include "ArmatureLoader.h"

USING_NS_CC;
USING_NS_CC_EXT;

CRole::CRole(void)
{
    m_fB2Width = 4.4f;
    m_fB2Height = 6.0f;
    m_nAxeType = ROLEID_NORMAXE;
    m_bIsReload = true;
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

void CRole::onEnter()
{
    CGameObject::onEnter();
    // 监听消息
    CCNotificationCenter::sharedNotificationCenter()->addObserver(
        this, callfuncO_selector(CRole::OnChangeAxe), MSG_UICHANGEAXE, NULL);
    // 设置动作回调
    getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(CRole::OnMovementEvent));

    // 换上武器装备 Sword
    std::string sWeaponName[] = {"00_01.png", "00_02.png", "00_03.png", "00_04.png", "00_05.png"};
    vector<CCNode*> vecSword;
    for (int i = 0; i < sizeof(sWeaponName)/sizeof(sWeaponName[0]); ++i)
    {
        vecSword.push_back(CCSprite::create(sWeaponName[i].c_str()));
    }
    
    for (unsigned int i = 0; i < vecSword.size(); ++i)
    {
        getBone("00")->addDisplay(vecSword[i], i);
    }

    getBone("00")->changeDisplayWithIndex(0, true);
    getBone("00")->setOpacity(0.0f);
    //getBone("00")->setScale(0.8f);
}

void CRole::onExit()
{
    CGameObject::onExit();
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, MSG_UICHANGEAXE);
}

int CRole::GetRoleType()
{
    return ROLETYPE_HERO;
}

void CRole::ThrowAxe()
{
    m_bIsReload = false;
    getAnimation()->stop();
    getBone("00")->setOpacity(255.0f);
    PlayAction("Attack", -1, -1, 0);
}

void CRole::OnMovementEvent(CCArmature *armature, MovementEventType movementType, const char * movementID)
{
    std::string id = movementID;

    if (movementType == COMPLETE)
    {
        if (id.compare("Attack") == 0)
        {
            m_bIsReload = true;
            getBone("00")->setOpacity(0);
            armature->getAnimation()->play("Idle");
            CCNotificationCenter::sharedNotificationCenter()->postNotification(MSG_ROLEACOMPLETE);
        }
    }
    else if(movementType == LOOP_COMPLETE)
    {
        if (id.compare("Idle") == 0)
        {
            //m_bIsReload = true;
        }
    }
}

void CRole::OnChangeAxe(CCObject *pObj)
{
    int nTag = dynamic_cast<CCNode*>(pObj)->getTag();
    int index = nTag - ROLEID_NORMAXE;

    m_nAxeType = nTag;
    getBone("00")->changeDisplayWithIndex(index, true);
}