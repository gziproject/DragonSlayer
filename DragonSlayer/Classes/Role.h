#ifndef __ROLE_H__
#define __ROLE_H__

#include "GameObject.h"

class CRole : 
    public CGameObject
{
public:
    CRole(void);
    ~CRole(void);

public:

    // 实例化一个对象
    static CGameObject* create(int rid);

    virtual void onEnter();
    virtual void onExit();
    virtual void update(float dt);

    // 角色类型
    virtual int GetRoleType();
    // 获得斧子类型
    int GetAxeType() { return m_nAxeType; }
    // 投掷斧子
    void ThrowAxe();
    // 重新载入斧子是否完成
    bool IsReload() { return m_bIsReload; }

private:
    
    void OnMovementEvent(cocos2d::extension::CCArmature *armature, cocos2d::extension::MovementEventType movementType, const char *movementID);
    void OnChangeAxe(cocos2d::CCObject *pObj);

private:

    int m_nAxeType;
    bool m_bIsReload;
};

#endif //__ROLE_H__
