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

    // ʵ����һ������
    static CPhysicsObject* create(int rid);
    // ��ɫ����
    virtual int GetRoleType();
    // ������
    virtual float GetPower() { return m_fPower; } 
    // ����
    virtual void Attack(CGameObject *pDragon);

protected:

    float               m_fPower;           // ���ӹ�����  
};

#endif // __AXE_H__

