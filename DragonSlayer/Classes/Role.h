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
    // ��ø�������
    int GetAxeType() { return m_nAxeType; }
    // Ͷ������
    void ThrowAxe();
    // �������븫���Ƿ����
    bool IsReload() { return m_bIsReload; }

private:
    
    void OnMovementEvent(cocos2d::extension::CCArmature *armature, cocos2d::extension::MovementEventType movementType, const char *movementID);
    void OnChangeAxe(cocos2d::CCObject *pObj);

private:

    int m_nAxeType;
    bool m_bIsReload;
};

#endif //__ROLE_H__
