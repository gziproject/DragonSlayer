#include "GameUILayer.h"
#include "DGameDef.h"
#include "Waterpump.h"

USING_NS_CC;

CGameUILayer::CGameUILayer(void)
{
    m_pAtlasScore = NULL;
    m_pAtlasMoney = NULL;
    m_nHpCnt = 0;
    m_nScore = 0;
}

CGameUILayer::~CGameUILayer(void)
{
}

void CGameUILayer::onEnter()
{
    CCLayer::onEnter();
    CCSize visiableView = CCDirector::sharedDirector()->getWinSize();

    // 生命值
    InitHp();

    // 最上部的分数, 金钱
    m_pAtlasScore = CCLabelAtlas::create("0123456789", "UI_02_05.png",48, 57, '0');
    m_pAtlasScore->setPosition(ccp(visiableView.width/2 - 100, visiableView.height - 80));
    addChild(m_pAtlasScore);

    m_pAtlasMoney = CCLabelAtlas::create("0123456789", "UI_02_05.png",48, 57, '0');
    m_pAtlasMoney->setPosition(ccp(visiableView.width/2 - 100, visiableView.height - 160));
    ccColor3B cGold = {251,216,96};
    m_pAtlasMoney->setColor(cGold);
    addChild(m_pAtlasMoney);

    // 分数钱旁边的暂停按钮
    CCMenuItemImage *pItemPause = CCMenuItemImage::create(
        "UI_02_03.png", "UI_02_04.png", this, menu_selector(CGameUILayer::onGamePause)); 
    CCMenu *pMenuPause = CCMenu::create(pItemPause, NULL);
    pMenuPause->setPosition(ccp(
        visiableView.width - pItemPause->getContentSize().width/2 - 80, 
        visiableView.height - pItemPause->getContentSize().height/2 - 80));
    addChild(pMenuPause);

    // 最下部有水
    CCSprite *pWater = CCSprite::create("water_01_02.png");
    pWater->setPosition(ccp(visiableView.width/2, pWater->getContentSize().height/2));
    addChild(pWater);
    
    // 水上面的船
    CCSprite *pShip = CCSprite::create("ship_01_01.png");
    pShip->setPosition(ccp(visiableView.width/2, pShip->getContentSize().height/2 + pWater->getContentSize().height));
    addChild(pShip);
    
    // 灌水泵
    CWaterpump *pWaterPump = CWaterpump::create();
    addChild(pWaterPump);   
    // 未add之前, contentsize为(0, 0); 将这句移到add之前, 设置位置就会有问题
    pWaterPump->setPosition(ccp(visiableView.width/2, pWaterPump->getContentSize().height/2));
}

void CGameUILayer::onExit()
{
    CCLayer::onExit();
}

void CGameUILayer::AddScore(int score)
{
    m_nScore += score;
    char szTemp[8] = {0};
    sprintf(szTemp, "%d", m_nScore);
    m_pAtlasMoney->setString(szTemp);
}

void CGameUILayer::AddMoney(int money)
{
    CPlayerAccount::GetAccountInstance()->AddPlayerAccountMoney(money);
    int money = CPlayerAccount::GetAccountInstance()->GetAccountsMoney();

    char szMoney[8] = {0};
    sprintf(szMoney, "%d", money);
    m_pAtlasMoney->setString(szMoney);
}

void CGameUILayer::ChangeHP(int upVal)
{
    int nCurHp = m_nHpCnt;
    m_nHpCnt += upVal;
    while(nCurHp != m_nHpCnt && nCurHp >= 0)
    {
        // 加血的
        if (nCurHp < m_nHpCnt)
        {
            m_pHpVec[nCurHp]->setDisabledImage(CCSprite::create("UI_02_02.png"));
            nCurHp++;
        }
        else //扣血的
        {
            m_pHpVec[nCurHp]->setDisabledImage(CCSprite::create("UI_02_01.png"));
            nCurHp--;
        }
    }
}

bool CGameUILayer::InitHp()
{
    CCSize visiableView = CCDirector::sharedDirector()->getWinSize();
    CCMenu *pMenuHP = CCMenu::create();
    pMenuHP->setAnchorPoint(CCPointZero);
    m_nHpCnt = 3;
    for (int i = 0; i < m_nHpCnt; ++i)
    {
        CCMenuItemImage *pHp = CCMenuItemImage::create(
            "UI_02_02.png", "UI_02_01.png", "UI_02_02.png", NULL, NULL);
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
    ChangeHP(-1);
    if (m_nHpCnt <= 0)
    {
        //GameOver
        //提示补充生命或游戏结束
    }
}

void CGameUILayer::onGamePause(cocos2d::CCObject *pSender)
{

}