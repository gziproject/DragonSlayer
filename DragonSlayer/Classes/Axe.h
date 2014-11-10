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
    // 初始化一些数据
    virtual void InitWithRid(int rid);
    // 攻击力
    virtual float GetPower() { return m_fPower; } 
    // 攻击
    virtual void Attack(CGameObject *pDragon);
    // 移除自己
    virtual void RemoveSelf();
    // 
    virtual void onEnter();

protected:

    float               m_fPower;           // 斧子攻击力 
    int                 m_nLevel;           // 斧子等级
    float               m_fExtraPower;      // 额外伤害
};

#endif // __AXE_H__

