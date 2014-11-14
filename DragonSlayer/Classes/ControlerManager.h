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

    // 射击的角度
    float GetShootAngle();
    void SetShootAngle(float angles);

    // 获得射击力度
    int GetShootForce();
    void SetShootForce(int force);

    // 是否暂停游戏
    bool IsGamePause();
    void SetGamePause(bool pause = true);

private:

    static CControlerManager    *m_Instance;
    float                        m_fShootAngle;
    int                          m_nShootForce;
    bool                         m_bGamePause;
};


#endif //__CONTROLORMANAGER_H__
