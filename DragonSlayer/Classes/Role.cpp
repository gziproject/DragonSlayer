#include "Role.h"
#include "ArmatureLoader.h"
#include "ControlerManager.h"

USING_NS_CC;
USING_NS_CC_EXT;

CRole::CRole(void)
{
    m_fB2Width = 2.0f;
    m_fB2Height = 3.0f;
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
    std::string sWeaponName[] = {
        "00_01.png", "00_02.png", 
        "00_03.png", "00_04.png", 
        "00_05.png"};

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
}

void CRole::onExit()
{
    CGameObject::onExit();
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, MSG_UICHANGEAXE);
}

void CRole::update(float dt)
{
    CGameObject::update(dt);
    CCSize visiableView = CCDirector::sharedDirector()->getWinSize();
    // 是否翻转英雄反向, 并且根据英雄所在的位置换算出斧子投掷的角度    
    float dist = abs(getPositionX() - visiableView.width/2);
    float maxDist = visiableView.width/2 - 330;
    float angles = dist*15/maxDist;
    if (getPositionX() > visiableView.width/2)
    {
        setScaleX(-1.0f);
        CControlerManager::GetInstance()->SetShootAngle(angles);
    }
    else
    {
        setScaleX(1.0f);
        CControlerManager::GetInstance()->SetShootAngle(-1*angles);
    }
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
    int nTag = dynamic_cast<CCMenuItemSprite*>(pObj)->getTag();
    int index = nTag - ROLEID_NORMAXE;

    m_nAxeType = nTag;
    getBone("00")->changeDisplayWithIndex(index, true);
}