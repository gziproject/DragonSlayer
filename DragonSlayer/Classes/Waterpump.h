#ifndef __WATERPUMP_H__
#define __WATERPUMP_H__

#include "cocos2d.h"

class CWaterpump : public cocos2d::CCSprite
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

    cocos2d::CCMenuItemSprite *initMenuItemWithFiles(const char *normal, const char *selected, const char *disable, cocos2d::SEL_MenuHandler selector);
    void onSelectedMenuItem(cocos2d::CCObject *pSender);

private:

    cocos2d::CCSprite        *m_pIndicator;         // 指示针
    cocos2d::CCProgressTimer *m_pPump;              // 灌水计时器
    cocos2d::CCSprite        *m_pFuryPower;         // 怒气值
    int                      m_nCurFuryPower;          // 当前怒气值
    int                      m_nMaxFuryPower;            // 最大怒气值
};

#endif //__WATERPUMP_H__
