#include "GameUILayer.h"
#include "DGameDef.h"
#include "Waterpump.h"

USING_NS_CC;

CGameUILayer::CGameUILayer(void)
{
}

CGameUILayer::~CGameUILayer(void)
{
}

void CGameUILayer::onEnter()
{
    CCLayer::onEnter();
    CCSize visiableView = CCDirector::sharedDirector()->getWinSize();

    // 最上部的分数, 生命值等等

    // 最下部有水
    CCSprite *pWater = CCSprite::create("water_01_02.png");
    addChild(pWater);
    pWater->setPosition(ccp(visiableView.width/2, pWater->getContentSize().height/2));

    // 水上面的船
    CCSprite *pShip = CCSprite::create("ship_01_01.png");
    addChild(pShip);
    pShip->setPosition(ccp(visiableView.width/2, pShip->getContentSize().height/2 + pWater->getContentSize().height));

    // 灌水泵
    CWaterpump *pWaterPump = CWaterpump::create();
    addChild(pWaterPump);
    pWaterPump->setPosition(ccp(visiableView.width/2, pWaterPump->getContentSize().height/2));

}

void CGameUILayer::onExit()
{
    CCLayer::onExit();
}
