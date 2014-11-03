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
    // ��ɫ����
    virtual int GetRoleType();
    // Ͷ������
    void ThrowAxe();
};

#endif //__ROLE_H__
