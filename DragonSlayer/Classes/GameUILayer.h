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

private:

};

#endif // __GAMEUILAYER_H__
