#include "Waterpump.h"
#include "DGameDef.h"
#include "ControlerManager.h"
#include <string.h>

USING_NS_CC;

static const char *szItemNormal[] = {"UI_07_02.png", "UI_06_02.png", "UI_05_02.png", "UI_08_02.png"};
static const char *szItemSelected[] = {"UI_07_03.png", "UI_06_03.png", "UI_05_03.png", "UI_08_03.png"};
static const char *szItemDisable[] = {"UI_07_01.png", "UI_06_01.png", "UI_05_01.png", "UI_08_01.png"};

static const int Tag_ItemFnt = 1000;

CWaterpump::CWaterpump(void)
{
    m_pIndicator = NULL;
    m_pPump = NULL;
    m_pFuryPower = NULL;
    m_nCurFuryPower = 0;
    m_nMaxFuryPower = 100;
}

CWaterpump::~CWaterpump(void)
{
}

void CWaterpump::onEnter()
{
    CCSprite::onEnter();

    CCSize visiableView = CCDirector::sharedDirector()->getWinSize();
    // 距离底部距离, 等同与怒气条的高度
    float fBottomHeight = 65.0f;

    // 监听玩家攻击
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, 
        callfuncO_selector(CWaterpump::onRoleAttackCallback), 
        MSG_ROLEACOMPLETE, NULL);

    CCSprite *pumpBg = CCSprite::create("UI_01_01.png");
    addChild(pumpBg);
    pumpBg->setPosition(ccp(visiableView.width/2, pumpBg->getContentSize().height/2));
    this->setContentSize(pumpBg->getContentSize());

    // 灌水彩色图
    CCProgressTo *to1 = CCProgressTo::create(3, 100);
    m_pPump = CCProgressTimer::create(CCSprite::create("UI_01_04.png"));
    m_pPump->setAnchorPoint(ccp(0.5f, 0.0f));
    m_pPump->setType(kCCProgressTimerTypeBar);
    m_pPump->setMidpoint(ccp(0,0));
    m_pPump->setBarChangeRate(ccp(0, 1));
    m_pPump->setPosition(ccp(visiableView.width/2 + 1, fBottomHeight));
    m_pPump->runAction(CCRepeatForever::create(to1));
    addChild(m_pPump);

    // 指示针
    m_pIndicator = CCSprite::create("UI_01_05.png");
    m_pIndicator->setAnchorPoint(ccp(0.5f, 0.0f));
    m_pIndicator->setPosition(ccp(visiableView.width/2, fBottomHeight));
    addChild(m_pIndicator);

    // 怒气值
    m_pFuryPower = CCSprite::create("UI_01_03.png", CCRectMake(0,0,1090,44));
    m_pFuryPower->setAnchorPoint(ccp(0.0f, 0.5f));
    ccTexParams params = {GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE};
    m_pFuryPower->getTexture()->setTexParameters(&params);
    m_pFuryPower->setPosition(ccp(visiableView.width/2 - 545, 44));
    m_pFuryPower->setScaleX(0.5f);
    addChild(m_pFuryPower, -1);

    CCSprite *pFuryBg = CCSprite::create("UI_01_02.png", CCRectMake(0,0,1090,44));
    pFuryBg->getTexture()->setTexParameters(&params);
    pFuryBg->setPosition(ccp(visiableView.width/2, 44));
    addChild(pFuryBg, -2);

    //菜单
    //普通斧子用来传递给角色数据, 不做显示用
    m_pNormalItem = initMenuItemWithFiles(szItemNormal[0], szItemSelected[0], szItemDisable[0], menu_selector(CWaterpump::onSelectedMenuItem));
    m_pNormalItem->setTag(ROLEID_NORMAXE);
    m_pNormalItem->setVisible(false);

    CCMenuItemSprite *pFireItem = initMenuItemWithFiles(szItemNormal[0], szItemSelected[0], szItemDisable[0], menu_selector(CWaterpump::onSelectedMenuItem));
    pFireItem->setTag(ROLEID_FIREAXE);
    CCMenuItemSprite *pIceItem = initMenuItemWithFiles(szItemNormal[1], szItemSelected[1], szItemDisable[1], menu_selector(CWaterpump::onSelectedMenuItem));
    pIceItem->setTag(ROLEID_ICEAXE);
    CCMenuItemSprite *pBaneItem = initMenuItemWithFiles(szItemNormal[2], szItemSelected[2], szItemDisable[2], menu_selector(CWaterpump::onSelectedMenuItem));
    pBaneItem->setTag(ROLEID_BANEAXE);
    CCMenuItemSprite *pWindItem = initMenuItemWithFiles(szItemNormal[3], szItemSelected[3], szItemDisable[3], menu_selector(CWaterpump::onSelectedMenuItem));
    pWindItem->setTag(ROLEID_WINDAXE);

    CCMenu *pMenu = CCMenu::create(pFireItem, pIceItem, pBaneItem, pWindItem, NULL);
    float fItemHeight = pFireItem->getContentSize().height;
    float fItemWidth = pFireItem->getContentSize().width;
    float fPumpWidth = m_pPump->getContentSize().width;
    pFireItem->setPosition(ccp(visiableView.width/2 - fPumpWidth/2 - (1.5f*fItemWidth), fItemHeight/2));
    pIceItem->setPosition(ccp(visiableView.width/2 - fPumpWidth/2 - (0.5f*fItemWidth), fItemHeight/2));
    pBaneItem->setPosition(ccp(visiableView.width/2 + fPumpWidth/2 + (0.5f*fItemWidth), fItemHeight/2));
    pWindItem->setPosition(ccp(visiableView.width/2 + fPumpWidth/2 + (1.5f*fItemWidth), fItemHeight/2));

    pMenu->setPosition(ccp(0, fBottomHeight));
    addChild(pMenu);

    scheduleUpdate();
}

void CWaterpump::onExit()
{
    CCSprite::onExit();
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, MSG_ROLEACOMPLETE);
}

void CWaterpump::update(float dt)
{
    int power = m_pPump->getPercentage()/20;
    CControlerManager::GetInstance()->SetShootForce(power);

    // 更新角度
    float angles = CControlerManager::GetInstance()->GetShootAngle();
    m_pIndicator->setRotation(angles);
}

void CWaterpump::addFuryPower(int power)
{
    if (m_nCurFuryPower < m_nMaxFuryPower)
    {
        m_nCurFuryPower += power;
        float scalex = float(m_nCurFuryPower / m_nMaxFuryPower);
        if (scalex >= 1.0f)
        {
            scalex = 1.0f;
            m_pFuryPower->setScaleX(scalex);
        }
    }
}

void CWaterpump::clearFuryPower()
{
    m_nCurFuryPower = 0;
    m_pFuryPower->setScaleX(0.0f);
}

CCMenuItemSprite *CWaterpump::initMenuItemWithFiles(const char *normal, const char *selected, const char *disable, SEL_MenuHandler selector)
{
    CCSprite *pNormal = CCSprite::create(normal);
    CCSprite *pSelected = CCSprite::create(selected);
    CCSprite *pDisable = CCSprite::create(disable);

    CCMenuItemSprite *pItem = CCMenuItemSprite::create(pNormal, pSelected, pDisable, this, selector);
    int cnt = 0;
    char szCntStr[8] = {0};
    sprintf(szCntStr, "%d", cnt);
    CCLabelAtlas *pCntFnt = CCLabelAtlas::create(szCntStr, "UI_02_05.png", 48, 57, '0');
    pCntFnt->setAnchorPoint(ccp(1, 0));
    pCntFnt->setPosition(ccp(pItem->getContentSize().width, 0));
    pItem->addChild(pCntFnt, 1, Tag_ItemFnt);
    
    return pItem;
}

void CWaterpump::onSelectedMenuItem(cocos2d::CCObject *pSender)
{
    // 条件判定, 斧子是否还有
    if (NULL != m_pSelectedItem)
    {
        m_pSelectedItem->unselected();
    }

    m_pSelectedItem = dynamic_cast<CCMenuItemSprite*>(pSender);
    int nAxeType = m_pSelectedItem->getTag();
    int nRemainAxe = 1;
    if (nRemainAxe > 0)
    {
        CCNotificationCenter::sharedNotificationCenter()->postNotification(MSG_UICHANGEAXE, pSender);
    }
    else
    {
        CCNotificationCenter::sharedNotificationCenter()->postNotification(MSG_UICHANGEAXE, m_pNormalItem);
        m_pSelectedItem = m_pNormalItem;
    }

    m_pSelectedItem->selected();
}

void CWaterpump::onRoleAttackCallback(cocos2d::CCObject *pObj)
{
    // 攻击完, 斧子是否还有
    if (m_pSelectedItem != m_pNormalItem)
    {
        int nRemainAxe = 1;
        if (nRemainAxe <= 0)
        {
            m_pSelectedItem->unselected();
            m_pSelectedItem = m_pNormalItem;
            CCNotificationCenter::sharedNotificationCenter()->postNotification(MSG_UICHANGEAXE, m_pNormalItem);
            m_pSelectedItem->selected();
        }
    }
}