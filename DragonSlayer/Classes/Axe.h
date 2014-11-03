#ifndef __AXE_H__
#define __AXE_H__

#include "PhysicsObject.h"

class CGameObject;
class CAxe : public CPhysicsObject
{
public:
    CAxe(void);
    ~CAxe(void);

public:

    // 实例化一个对象
    static CPhysicsObject* create(int rid);
    // 角色类型
    virtual int GetRoleType();
    // 攻击力
    virtual float GetPower() { return m_fPower; } 
    // 攻击
    virtual void Attack(CGameObject *pDragon);

protected:

    float               m_fPower;           // 斧子攻击力  
};

#endif // __AXE_H__

