#include "ArmatureLoader.h"
#include "cocos2d.h"
#include "cocos-ext.h"

using namespace std;
USING_NS_CC;
USING_NS_CC_EXT;


ArmatureLoader::ArmatureLoader(void)
{
}

ArmatureLoader::~ArmatureLoader(void)
{
}

ArmatureLoader* ArmatureLoader::m_Instance = NULL;
ArmatureLoader* ArmatureLoader::GetInstance()
{
    if (NULL == m_Instance)
    {
        m_Instance = new ArmatureLoader;    
    }

    return m_Instance;
}

void ArmatureLoader::Destroy()
{
    if (NULL != m_Instance)
    {
        delete m_Instance;
        m_Instance = NULL;
    }
}

bool ArmatureLoader::LoadArmatureWithFile(const char *szFile)
{
    std::list<std::string>::iterator iter = std::find(m_LoadFiles.begin(), m_LoadFiles.end(), szFile);
    if (iter != m_LoadFiles.end())
    {
        return false;
    }

    m_LoadFiles.push_back(szFile);

    CCDictionary *pDict = CCDictionary::createWithContentsOfFile(szFile);
    if (NULL == pDict)
        return false;

    CCArray *pArray = pDict->allKeys();

    CCObject *pObj = NULL;
    CCARRAY_FOREACH(pArray, pObj)
    {  
        CCString *key = dynamic_cast<CCString *>(pObj);
        int armid = atoi(key->getCString());
        m_ArmaRes[armid] = pDict->valueForKey(key->getCString())->getCString();

        char szExportFile[128] = {0};
        sprintf(szExportFile, "%s.ExportJson", m_ArmaRes[armid].c_str());

        CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(szExportFile);

//         if (NULL != str)
//         {
//             CCLog("index %d str %s", i++, str->getCString());
//             CCLog("value of key %s", pDict->valueForKey(str->getCString())->getCString());
//         }
    }

    return true;
}

CCArmature *ArmatureLoader::CreateArmature(int armid)
{
    if (m_ArmaRes.find(armid) != m_ArmaRes.end())
    {
        return CCArmature::create(m_ArmaRes[armid].c_str());
    }

    return NULL;
}

std::string ArmatureLoader::GetArmatureName(int armid)
{
    return m_ArmaRes[armid];
}
