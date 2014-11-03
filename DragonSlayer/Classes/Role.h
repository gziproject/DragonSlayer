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
    // 角色类型
    virtual int GetRoleType();
    // 投掷斧子
    void ThrowAxe();
};

#endif //__ROLE_H__
