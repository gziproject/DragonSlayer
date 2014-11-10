#include "GameUILayer.h"
#include "DGameDef.h"

USING_NS_CC;


static const char *szItemNormal[] = {"UI_07_02.png", "UI_06_02.png", "UI_05_02.png", "UI_08_02.png"};
static const char *szItemSelected[] = {"UI_07_03.png", "UI_06_03.png", "UI_05_03.png", "UI_08_03.png"};
static const char *szItemDisable[] = {"UI_07_01.png", "UI_06_01.png", "UI_05_01.png", "UI_08_01.png"};

CGameUILayer::CGameUILayer(void)
{
}

CGameUILayer::~CGameUILayer(void)
{
}

void CGameUILayer::onEnter()
{
    CCLayer::onEnter();
    CCSize visableView = CCDirector::sharedDirector()->getWinSize();

    CCMenuItemSprite *pFireItem = initMenuItemWithFiles(szItemNormal[0], szItemSelected[0], szItemDisable[0], menu_selector(CGameUILayer::onSelectedMenuItem));
    pFireItem->setTag(ROLEID_FIREAXE);
    CCMenuItemSprite *pIceItem = initMenuItemWithFiles(szItemNormal[1], szItemSelected[1], szItemDisable[1], menu_selector(CGameUILayer::onSelectedMenuItem));
    pFireItem->setTag(ROLEID_ICEAXE);
    CCMenuItemSprite *pBaneItem = initMenuItemWithFiles(szItemNormal[2], szItemSelected[2], szItemDisable[2], menu_selector(CGameUILayer::onSelectedMenuItem));
    pFireItem->setTag(ROLEID_BANEAXE);
    CCMenuItemSprite *pWindItem = initMenuItemWithFiles(szItemNormal[3], szItemSelected[3], szItemDisable[3], menu_selector(CGameUILayer::onSelectedMenuItem));
    pFireItem->setTag(ROLEID_WINDAXE);

    CCMenu *pMenu = CCMenu::create(pFireItem, pIceItem, pBaneItem, pWindItem, NULL);
    pMenu->alignItemsVertically();
    pMenu->setPosition(ccp(visableView.width/2, visableView.height/2));
}

void CGameUILayer::onExit()
{
    CCLayer::onExit();
}

CCMenuItemSprite *CGameUILayer::initMenuItemWithFiles(const char *normal, const char *selected, const char *disable, SEL_MenuHandler selector)
{
    CCSprite *pNormal = CCSprite::create(normal);
    CCSprite *pSelected = CCSprite::create(selected);
    CCSprite *pDisable = CCSprite::create(disable);

    return CCMenuItemSprite::create(pNormal, pSelected, pDisable, selector);
}

void CGameUILayer::onSelectedMenuItem(cocos2d::CCObject *pSender)
{
    // 条件判定, 斧子是否还有
    if (1)
    {
        CCNotificationCenter::sharedNotificationCenter()->postNotification(MSG_UICHANGEAXE, pSender);
    }
}
