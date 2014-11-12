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

    // ���ϲ��ķ���, ����ֵ�ȵ�

    // ���²���ˮ
    CCSprite *pWater = CCSprite::create("water_01_02.png");
    addChild(pWater);
    pWater->setPosition(ccp(visiableView.width/2, pWater->getContentSize().height/2));

    // ˮ����Ĵ�
    CCSprite *pShip = CCSprite::create("ship_01_01.png");
    addChild(pShip);
    pShip->setPosition(ccp(visiableView.width/2, pShip->getContentSize().height/2 + pWater->getContentSize().height));

    // ��ˮ��
    CWaterpump *pWaterPump = CWaterpump::create();
    addChild(pWaterPump);
    pWaterPump->setPosition(ccp(visiableView.width/2, pWaterPump->getContentSize().height/2));

}

void CGameUILayer::onExit()
{
    CCLayer::onExit();
}
