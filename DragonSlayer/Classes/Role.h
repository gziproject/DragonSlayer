#ifndef __ROLE_H__
#define __ROLE_H__

#include "GameObject.h"

class CRole : public CGameObject
{
public:
    CRole(void);
    ~CRole(void);

public:

    // ʵ����һ������
    static CGameObject* create(int rid);

    void onEnter();
    void onExit();

    // ��ɫ����
    virtual int GetRoleType();
    // Ͷ������
    void ThrowAxe();
    // �Ƿ�������
    bool IsReload() { return m_bIsReload; }

private:
    
    void OnMovementEvent(cocos2d::extension::CCArmature *armature, cocos2d::extension::MovementEventType movementType, const char *movementID);
    void OnChangeAxe(cocos2d::CCObject *pObj);

private:

    bool m_bIsReload;
};

#endif //__ROLE_H__
