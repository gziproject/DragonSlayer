#include "GameObject.h"

class CMonster : public CGameObject
{
public:
    CMonster(void);
    ~CMonster(void);

public:

    // ʵ����һ������
    static CGameObject* create(int rid);
    // ��ɫ����
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

