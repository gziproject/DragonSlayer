#ifndef __LOADINGSTAGE_H__
#define __LOADINGSTAGE_H__

#include "cocos2d.h"

class CLoadingStage : public cocos2d::CCLayer
{
public:
    CLoadingStage(void);
    ~CLoadingStage(void);

public:

    // ��������
    static cocos2d::CCScene* scene();
    // ���������Դ, �ò��Ϊ�˼�����Դ, ��Ҫʱת�ջ�~
    void onEnter();

    void onExit();

    CREATE_FUNC(CLoadingStage);

};

#endif //__LOADINGSTAGE_H__
