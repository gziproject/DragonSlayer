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

    // 更新射击角度, 放在重力感应回调中, 更新射击的角度
    void UpdateShootAngle(float distance);
    // 获得射击角度
    float GetShootAngle();
    // 获得射击力度
    int GetShootForce();
    void SetShootForce(int force);

private:

    static CControlerManager    *m_Instance;
    float                        m_fShootAngle;
    int                          m_nShootForce;
};


#endif //__CONTROLORMANAGER_H__
