#include "GameObject.h"

class CMonster : public CGameObject
{
public:
    CMonster(void);
    ~CMonster(void);

public:

    // 实例化一个对象
    static CGameObject* create(int rid);
    // 角色类型
    virtual int GetRoleType();
    //
    virtual bool IsTouchGroundRemove() { return m_bIsTouchGroundRemove; }
    //
    virtual float Injure(int power);
    //
    virtual void Die();

private:

    bool            m_bIsTouchGroundRemove;
};

