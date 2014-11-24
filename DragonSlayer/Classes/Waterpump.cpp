#include "Waterpump.h"
#include "DGameDef.h"
#include "ControlerManager.h"
#include "PlayerAccount.h"
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
    m_pSelectedItem = NULL;
    m_fCurFuryPower = 0;
    m_fMaxFuryPower = 100;
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
    m_pFuryPower->setScaleX(0.0f);
    addChild(m_pFuryPower, -1);

    CCSprite *pFuryBg = CCSprite::create("UI_01_02.png", CCRectMake(0,0,1090,44));
    pFuryBg->getTexture()->setTexParameters(&params);
    pFuryBg->setPosition(ccp(visiableView.width/2, 44));
    addChild(pFuryBg, -2);

    //菜单
    //普通斧子用来传递给角色数据, 不做显示用
    m_pNormalAxeItem = initMenuItemWithFiles(ROLEID_NORMAXE, szItemNormal[0], szItemSelected[0], szItemDisable[0], menu_selector(CWaterpump::onSelectedMenuItem));
    m_pNormalAxeItem->setVisible(false);

    CCMenuItemSprite *pFireItem = initMenuItemWithFiles(ROLEID_FIREAXE, szItemNormal[0], szItemSelected[0], szItemDisable[0], menu_selector(CWaterpump::onSelectedMenuItem));
    CCMenuItemSprite *pIceItem = initMenuItemWithFiles(ROLEID_ICEAXE, szItemNormal[1], szItemSelected[1], szItemDisable[1], menu_selector(CWaterpump::onSelectedMenuItem));
    CCMenuItemSprite *pBaneItem = initMenuItemWithFiles(ROLEID_BANEAXE, szItemNormal[2], szItemSelected[2], szItemDisable[2], menu_selector(CWaterpump::onSelectedMenuItem));
    CCMenuItemSprite *pWindItem = initMenuItemWithFiles(ROLEID_WINDAXE, szItemNormal[3], szItemSelected[3], szItemDisable[3], menu_selector(CWaterpump::onSelectedMenuItem));

    CCMenu *pMenu = CCMenu::create(m_pNormalAxeItem, pFireItem, pIceItem, pBaneItem, pWindItem, NULL);
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
    if (m_fCurFuryPower < m_fMaxFuryPower)
    {
        m_fCurFuryPower += power;
        float scalex = m_fCurFuryPower / m_fMaxFuryPower;
        if (scalex >= 1.0f)
        {
            scalex = 1.0f;
        }

        m_pFuryPower->setScaleX(scalex);
    }
}

void CWaterpump::clearFuryPower()
{
    m_fCurFuryPower = 0;
    m_pFuryPower->setScaleX(0.0f);
}

CCMenuItemSprite *CWaterpump::initMenuItemWithFiles(int type, const char *normal, const char *selected, const char *disable, SEL_MenuHandler selector)
{
    CCSprite *pNormal = CCSprite::create(normal);
    CCSprite *pSelected = CCSprite::create(selected);
    CCSprite *pDisable = CCSprite::create(disable);

    CCMenuItemSprite *pItem = CCMenuItemSprite::create(pNormal, pSelected, pDisable, this, selector);
    int cnt = CPlayerAccount::GetAccountInstance()->GetAccountPropsNum(type);
    char szCntStr[8] = {0};
    sprintf(szCntStr, "%d", cnt);
    CCLabelAtlas *pCntFnt = CCLabelAtlas::create(szCntStr, "UI_02_05.png", 48, 57, '0');
    pCntFnt->setAnchorPoint(ccp(1, 0));
    pCntFnt->setPosition(ccp(pItem->getContentSize().width, 0));
    pItem->addChild(pCntFnt, 1, Tag_ItemFnt);
    pItem->setTag(type);
    return pItem;
}

void CWaterpump::onSelectedMenuItem(cocos2d::CCObject *pSender)
{
    // 条件判定, 斧子是否还有
    if (NULL != m_pSelectedItem)
    {
        m_pSelectedItem->unselected();
    }

    CCMenuItemSprite *pSelected = dynamic_cast<CCMenuItemSprite*>(pSender);
    int nAxeType = pSelected->getTag();
    int nRemainAxe = CPlayerAccount::GetAccountInstance()->GetAccountPropsNum(nAxeType);
    if (nRemainAxe > 0 && m_pSelectedItem != pSelected)
    {
        CCNotificationCenter::sharedNotificationCenter()->postNotification(MSG_UICHANGEAXE, pSender);
        m_pSelectedItem = pSelected;
    }
    else
    {
        CCNotificationCenter::sharedNotificationCenter()->postNotification(MSG_UICHANGEAXE, m_pNormalAxeItem);
        m_pSelectedItem = m_pNormalAxeItem;
    }

    m_pSelectedItem->selected();
}

void CWaterpump::onRoleAttackCallback(cocos2d::CCObject *pObj)
{
    // 攻击完, 斧子是否还有
    addFuryPower();
    if (m_pSelectedItem != m_pNormalAxeItem && m_pSelectedItem != NULL)
    {
        // 不是普通斧子, 斧子数量减少1个
        int nAxeType = m_pSelectedItem->getTag();
        int nRemainAxe = CPlayerAccount::GetAccountInstance()->GetAccountPropsNum(nAxeType);
        nRemainAxe -= 1;
        ResetAxeNum(m_pSelectedItem, nRemainAxe);

        CPlayerAccount::GetAccountInstance()->AddPlayerAccountProps(nAxeType, -1);
        
        if (nRemainAxe <= 0)
        {
            m_pSelectedItem->unselected();
            m_pSelectedItem = m_pNormalAxeItem;
            CCNotificationCenter::sharedNotificationCenter()->postNotification(MSG_UICHANGEAXE, m_pNormalAxeItem);
            m_pSelectedItem->selected();
        }
    }
}

void CWaterpump::ResetAxeNum(cocos2d::CCMenuItemSprite *pItem, int num)
{
    CCLabelAtlas *pItemFnt = dynamic_cast<CCLabelAtlas*>(pItem->getChildByTag(Tag_ItemFnt));
    if (NULL != pItemFnt)
    {
        char szNum[8] = {0};
        sprintf(szNum, "%d", num);
        pItemFnt->setString(szNum);
    }
}
