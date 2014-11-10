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

private:

    cocos2d::CCMenuItemSprite *initMenuItemWithFiles(const char *normal, const char *selected, const char *disable, cocos2d::SEL_MenuHandler selector);

    void onSelectedMenuItem(cocos2d::CCObject *pSender);

};

#endif // __GAMEUILAYER_H__
