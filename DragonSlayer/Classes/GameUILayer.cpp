#include "GameUILayer.h"
#include "DGameDef.h"
#include "Waterpump.h"

USING_NS_CC;

CGameUILayer::CGameUILayer(void)
{
    m_nHpCnt = 0;
}

CGameUILayer::~CGameUILayer(void)
{
}

void CGameUILayer::onEnter()
{
    CCLayer::onEnter();
    CCSize visiableView = CCDirector::sharedDirector()->getWinSize();

    // ����ֵ
    InitHp();

    // ���ϲ��ķ���, ��Ǯ
    m_pAtlasScore = CCLabelAtlas::create("0123456789", "UI_02_05.png",48, 57, '0');
    m_pAtlasScore->setPosition(ccp(visiableView.width/2 - 100, visiableView.height - 80));
    addChild(m_pAtlasScore);

    m_pAtlasMoney = CCLabelAtlas::create("0123456789", "UI_02_05.png",48, 57, '0');
    m_pAtlasMoney->setPosition(ccp(visiableView.width/2 - 100, visiableView.height - 160));
    ccColor3B cGold = {251,216,96};
    m_pAtlasMoney->setColor(cGold);
    addChild(m_pAtlasMoney);

    // ����Ǯ�Աߵ���ͣ��ť
    CCMenuItemImage *pItemPause = CCMenuItemImage::create("UI_02_03.png", "UI_02_04.png", this, menu_selector(CGameUILayer::onGamePause)); 
    CCMenu *pMenuPause = CCMenu::create(pItemPause, NULL);
    pMenuPause->setPosition(ccp(
        visiableView.width - pItemPause->getContentSize().width/2 - 80, 
        visiableView.height - pItemPause->getContentSize().height/2 - 80));
    addChild(pMenuPause);

    // ���²���ˮ
    CCSprite *pWater = CCSprite::create("water_01_02.png");
    pWater->setPosition(ccp(visiableView.width/2, pWater->getContentSize().height/2));
    addChild(pWater);
    
    // ˮ����Ĵ�
    CCSprite *pShip = CCSprite::create("ship_01_01.png");
    pShip->setPosition(ccp(visiableView.width/2, pShip->getContentSize().height/2 + pWater->getContentSize().height));
    addChild(pShip);
    
    // ��ˮ��
    CWaterpump *pWaterPump = CWaterpump::create();
    addChild(pWaterPump);   
    // δadd֮ǰ, contentsizeΪ(0, 0); ������Ƶ�add֮ǰ, ����λ�þͻ�������
    pWaterPump->setPosition(ccp(visiableView.width/2, pWaterPump->getContentSize().height/2));
}

void CGameUILayer::onExit()
{
    CCLayer::onExit();
}

bool CGameUILayer::InitHp()
{
    CCSize visiableView = CCDirector::sharedDirector()->getWinSize();
    CCMenu *pMenuHP = CCMenu::create();
    pMenuHP->setAnchorPoint(CCPointZero);
    m_nHpCnt = 3;
    for (int i = 0; i < m_nHpCnt; ++i)
    {
        CCMenuItemImage *pHp = CCMenuItemImage::create("UI_02_02.png", "UI_02_01.png", "UI_02_02.png", NULL, NULL);
        float width = pHp->getContentSize().width;
        float height = pHp->getContentSize().height;
        pHp->setEnabled(false);
        pHp->setPosition(ccp(width/2 + width*i, height/2));
        pMenuHP->addChild(pHp);
        m_pHpVec.push_back(pHp);
    }

    pMenuHP->setPosition(ccp(80, visiableView.height - 120));
    addChild(pMenuHP);
    
    return true;
}

void CGameUILayer::onRoleInjureCallback(cocos2d::CCObject *pObj)
{
    m_nHpCnt -= 1;
    m_pHpVec[m_nHpCnt]->setDisabledImage(CCSprite::create("UI_02_01.png"));

    if (m_nHpCnt <= 0)
    {
        //GameOver
        //��ʾ������������Ϸ����
    }
}

void CGameUILayer::onGamePause(cocos2d::CCObject *pSender)
{

}