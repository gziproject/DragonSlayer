#include "Waterpump.h"
#include "DGameDef.h"

USING_NS_CC;

static const char *szItemNormal[] = {"UI_07_02.png", "UI_06_02.png", "UI_05_02.png", "UI_08_02.png"};
static const char *szItemSelected[] = {"UI_07_03.png", "UI_06_03.png", "UI_05_03.png", "UI_08_03.png"};
static const char *szItemDisable[] = {"UI_07_01.png", "UI_06_01.png", "UI_05_01.png", "UI_08_01.png"};

static const int Tag_ItemFnt = 1000;

CWaterpump::CWaterpump(void)
{
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

    CCSprite *pumpBg = CCSprite::create("UI_01_01.png");
    addChild(pumpBg);
    pumpBg->setPosition(ccp(visiableView.width/2, pumpBg->getContentSize().height/2));
    this->setContentSize(pumpBg->getContentSize());

    // 灌水彩色图
    CCSprite *pPump = CCSprite::create("UI_01_04.png");
    pPump->setAnchorPoint(ccp(0.5f, 0.0f));
    pPump->setPosition(ccp(visiableView.width/2, fBottomHeight));
    addChild(pPump);

    // 指示针
    m_pIndicator = CCSprite::create("UI_01_05.png");
    m_pIndicator->setAnchorPoint(ccp(0.5f, 0.0f));
    m_pIndicator->setPosition(ccp(visiableView.width/2, fBottomHeight));
    addChild(m_pIndicator);

    //菜单
    CCMenuItemSprite *pFireItem = initMenuItemWithFiles(szItemNormal[0], szItemSelected[0], szItemDisable[0], menu_selector(CWaterpump::onSelectedMenuItem));
    pFireItem->setTag(ROLEID_FIREAXE);
    CCMenuItemSprite *pIceItem = initMenuItemWithFiles(szItemNormal[1], szItemSelected[1], szItemDisable[1], menu_selector(CWaterpump::onSelectedMenuItem));
    pFireItem->setTag(ROLEID_ICEAXE);
    CCMenuItemSprite *pBaneItem = initMenuItemWithFiles(szItemNormal[2], szItemSelected[2], szItemDisable[2], menu_selector(CWaterpump::onSelectedMenuItem));
    pFireItem->setTag(ROLEID_BANEAXE);
    CCMenuItemSprite *pWindItem = initMenuItemWithFiles(szItemNormal[3], szItemSelected[3], szItemDisable[3], menu_selector(CWaterpump::onSelectedMenuItem));
    pFireItem->setTag(ROLEID_WINDAXE);

    CCMenu *pMenu = CCMenu::create(pFireItem, pIceItem, pBaneItem, pWindItem, NULL);
    float fItemHeight = pFireItem->getContentSize().height;
    float fItemWidth = pFireItem->getContentSize().width;
    float fPumpWidth = pPump->getContentSize().width;
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

}

void CWaterpump::update(float dt)
{

}

CCMenuItemSprite *CWaterpump::initMenuItemWithFiles(const char *normal, const char *selected, const char *disable, SEL_MenuHandler selector)
{
    CCSprite *pNormal = CCSprite::create(normal);
    CCSprite *pSelected = CCSprite::create(selected);
    CCSprite *pDisable = CCSprite::create(disable);

    CCMenuItemSprite *pItem = CCMenuItemSprite::create(pNormal, pSelected, pDisable, selector);
    //     CCLabelBMFont *pFnt = CCLabelBMFont::create("00", szFontAxeCnt);
    //     pItem->addChild(pFnt, 1, Tag_ItemFnt);
    return pItem;
}

void CWaterpump::onSelectedMenuItem(cocos2d::CCObject *pSender)
{
    // 条件判定, 斧子是否还有
    if (1)
    {
        CCNotificationCenter::sharedNotificationCenter()->postNotification(MSG_UICHANGEAXE, pSender);
    }
}