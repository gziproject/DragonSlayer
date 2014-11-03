#ifndef __LOADINGSTAGE_H__
#define __LOADINGSTAGE_H__

#include "cocos2d.h"

class CLoadingStage : public cocos2d::CCLayer
{
public:
    CLoadingStage(void);
    ~CLoadingStage(void);

public:

    // 创建场景
    static cocos2d::CCScene* scene();
    // 进入加载资源, 该层就为了加载资源, 需要时转菊花~
    void onEnter();

    void onExit();

    CREATE_FUNC(CLoadingStage);

};

#endif //__LOADINGSTAGE_H__
