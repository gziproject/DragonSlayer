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

    // ����ĽǶ�
    float GetShootAngle();
    void SetShootAngle(float angles);

    // ����������
    int GetShootForce();
    void SetShootForce(int force);

    // �Ƿ���ͣ��Ϸ
    bool IsGamePause();
    void SetGamePause(bool pause = true);

private:

    static CControlerManager    *m_Instance;
    float                        m_fShootAngle;
    int                          m_nShootForce;
    bool                         m_bGamePause;
};


#endif //__CONTROLORMANAGER_H__
