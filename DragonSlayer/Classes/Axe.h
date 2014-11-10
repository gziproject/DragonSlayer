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
    // ��ʼ��һЩ����
    virtual void InitWithRid(int rid);
    // ������
    virtual float GetPower() { return m_fPower; } 
    // ����
    virtual void Attack(CGameObject *pDragon);
    // �Ƴ��Լ�
    virtual void RemoveSelf();
    // 
    virtual void onEnter();

protected:

    float               m_fPower;           // ���ӹ����� 
    int                 m_nLevel;           // ���ӵȼ�
    float               m_fExtraPower;      // �����˺�
};

#endif // __AXE_H__

