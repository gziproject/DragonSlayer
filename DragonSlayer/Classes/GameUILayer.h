#ifndef __GAMEUILAYER_H__
#define __GAMEUILAYER_H__

#include "cocos2d.h"

class CGameUILayer : 
    public cocos2d::CCLayer
{
public:
    CGameUILayer(void);
    ~CGameUILayer(void);

public:

    void onEnter();
    void onExit();
    CREATE_FUNC(CGameUILayer);

    void AddScore(int score);
    void AddMoney(int money);
    void ChangeHP(int upVal);

private:
    //初始化生命值
    bool InitHp();
    //玩家受伤消息
    void onRoleInjureCallback(cocos2d::CCObject *pObj);
    //玩家暂停游戏
    void onGamePause(cocos2d::CCObject *pSender);

private:

    cocos2d::CCLabelAtlas                    *m_pAtlasScore;
    cocos2d::CCLabelAtlas                    *m_pAtlasMoney;
    std::vector<cocos2d::CCMenuItemImage *>   m_pHpVec;
    int                                       m_nHpCnt;
    int                                       m_nScore;
};

#endif // __GAMEUILAYER_H__
