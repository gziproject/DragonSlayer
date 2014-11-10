
#ifndef __GAMECONFIG_H__
#define __GAMECONFIG_H__

#include <map>
#include "DConfigDef.h"

class CCsvLoader;
class CGameConfig
{
private:

    CGameConfig();
    ~CGameConfig();

public:
    
    static CGameConfig*       GetInstance();
    static void                 Destroy();

    // 系统启动读取配置接口
    void                        ReadConfig();

    
private:

    static CGameConfig                    *m_pIntance;
    CCsvLoader                              *m_pCsvLoader;
};

#endif //__GLOBALCONFIG_H__
