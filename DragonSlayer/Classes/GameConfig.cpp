#include "GameConfig.h"
#include "CsvLoader.h"

CGameConfig::CGameConfig()
{
    m_pCsvLoader = NULL;
}

CGameConfig::~CGameConfig()
{
    if (NULL != m_pCsvLoader)
    {
        delete m_pCsvLoader;
        m_pCsvLoader = NULL;
    }
}

CGameConfig* CGameConfig::m_pIntance = NULL;
CGameConfig* CGameConfig::GetInstance()
{
    if (NULL == m_pIntance)
    {
        m_pIntance = new CGameConfig;
    }

    return m_pIntance;
}

void CGameConfig::Destroy()
{
    if (NULL != m_pIntance)
    {
        delete m_pIntance;
        m_pIntance = NULL;
    }
}

void CGameConfig::ReadConfig()
{
    if (NULL == m_pCsvLoader)
    {
        m_pCsvLoader = new CCsvLoader;
    }


}
