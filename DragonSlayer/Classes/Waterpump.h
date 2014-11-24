#ifndef __WATERPUMP_H__
#define __WATERPUMP_H__

#include "cocos2d.h"

class CWaterpump : 
    public cocos2d::CCSprite
{
public:
    CWaterpump(void);
    ~CWaterpump(void);

public:

    void onEnter();
    void onExit();
    void update(float dt);
    CREATE_FUNC(CWaterpump);

    void addFuryPower(int power = 1);
    void clearFuryPower();

private:

    cocos2d::CCMenuItemSprite *initMenuItemWithFiles(int type, const char *normal, const char *selected, const char *disable, cocos2d::SEL_MenuHandler selector);
    void onSelectedMenuItem(cocos2d::CCObject *pSender);
    void onRoleAttackCallback(cocos2d::CCObject *pObj);
    void ResetAxeNum(cocos2d::CCMenuItemSprite *pItem, int num);

private:

    cocos2d::CCSprite        *m_pIndicator;         // 指示针
    cocos2d::CCProgressTimer *m_pPump;              // 灌水计时器
    cocos2d::CCSprite        *m_pFuryPower;         // 怒气值
    float                    m_fCurFuryPower;       // 当前怒气值
    float                    m_fMaxFuryPower;       // 最大怒气值

    cocos2d::CCMenuItemSprite *m_pNormalAxeItem;    // 普通斧子
    cocos2d::CCMenuItemSprite *m_pSelectedItem;     // 选中的斧子
};

#endif //__WATERPUMP_H__
