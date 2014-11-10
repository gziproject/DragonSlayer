
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

    // ϵͳ������ȡ���ýӿ�
    void                        ReadConfig();

    
private:

    static CGameConfig                    *m_pIntance;
    CCsvLoader                              *m_pCsvLoader;
};

#endif //__GLOBALCONFIG_H__
