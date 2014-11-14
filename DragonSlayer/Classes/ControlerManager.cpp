#include "ControlerManager.h"
#include <stdlib.h>

CControlerManager::CControlerManager(void)
    :m_fShootAngle(0.0f),
    m_nShootForce(0),
    m_bGamePause(false)
{
}

CControlerManager::~CControlerManager(void)
{
}

CControlerManager *CControlerManager::m_Instance = NULL;
CControlerManager *CControlerManager::GetInstance()
{
    if (NULL == m_Instance)
    {
        m_Instance = new CControlerManager;
    }

    return m_Instance;
}

void CControlerManager::Destroy()
{
    if (NULL != m_Instance)
    {
        delete m_Instance;
        m_Instance = NULL;
    }
}

void CControlerManager::SetShootAngle(float angles)
{
    m_fShootAngle = angles;
}

float CControlerManager::GetShootAngle()
{
    return m_fShootAngle;
}

int CControlerManager::GetShootForce()
{
    return m_nShootForce;
}

void CControlerManager::SetShootForce(int force) 
{ 
    m_nShootForce = force;
}

bool CControlerManager::IsGamePause()
{
    return m_bGamePause;
}

void CControlerManager::SetGamePause(bool pause)
{
    m_bGamePause = pause;
}
