#ifndef __CONTROLORMANAGER_H__
#define __CONTROLORMANAGER_H__

class CControlerManager
{
private:

    CControlerManager(void);
    ~CControlerManager(void);

public:
    
    static CControlerManager *GetInstance();
    static void Destroy();

    // ��������Ƕ�, ����������Ӧ�ص���, ��������ĽǶ�
    void UpdateShootAngle(float distance);
    // �������Ƕ�
    float GetShootAngle();
    // ����������
    int GetShootForce();
    void SetShootForce(int force);

private:

    static CControlerManager    *m_Instance;
    float                        m_fShootAngle;
    int                          m_nShootForce;
};


#endif //__CONTROLORMANAGER_H__
