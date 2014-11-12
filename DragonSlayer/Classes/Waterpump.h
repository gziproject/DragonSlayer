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

    cocos2d::CCMenuItemSprite *initMenuItemWithFiles(const char *normal, const char *selected, const char *disable, cocos2d::SEL_MenuHandler selector);
    void onSelectedMenuItem(cocos2d::CCObject *pSender);

private:

    cocos2d::CCSprite       *m_pIndicator;          // ÷∏ æ’Î
};

#endif //__WATERPUMP_H__
