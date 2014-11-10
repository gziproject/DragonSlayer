#ifndef __ROLE_H__
#define __ROLE_H__

#include "GameObject.h"

class CRole : public CGameObject
{
public:
    CRole(void);
    ~CRole(void);

public:

    // 实例化一个对象
    static CGameObject* create(int rid);

    void onEnter();
    void onExit();

    // 角色类型
    virtual int GetRoleType();
    // 投掷斧子
    void ThrowAxe();
    // 是否加载完成
    bool IsReload() { return m_bIsReload; }

private:
    
    void OnMovementEvent(cocos2d::extension::CCArmature *armature, cocos2d::extension::MovementEventType movementType, const char *movementID);
    void OnChangeAxe(cocos2d::CCObject *pObj);

private:

    bool m_bIsReload;
};

#endif //__ROLE_H__
