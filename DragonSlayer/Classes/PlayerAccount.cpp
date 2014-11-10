#include "PlayerAccount.h"
#include "cocos2d.h"

using namespace cocos2d;

#define     MAX_FILE_DATA          2048

#define     Rank_Name_0            "1000"
#define     Rank_Score_0           "2000"

#define     AccountFile            "kx_ds.png"

CPlayerAccount::CPlayerAccount()
    :m_listRankData(10)
{
    m_nAccount = 0;
    m_mapPropsData.clear();
}

CPlayerAccount::~CPlayerAccount()
{
}

CPlayerAccount*  CPlayerAccount::m_pAccountInstance = NULL;

CPlayerAccount *CPlayerAccount::GetAccountInstance()
{
	if (m_pAccountInstance == NULL)
	{
		m_pAccountInstance = new CPlayerAccount;
	}

	return m_pAccountInstance;
}

void CPlayerAccount::DestroyAccountInstance()
{
	if (NULL != m_pAccountInstance)
	{
		delete m_pAccountInstance;
		m_pAccountInstance = NULL;
	}
}

int	CPlayerAccount::GetAccountsMoney()
{
	return m_nAccount;
}

int CPlayerAccount::GetAccountPropsNum(int nPropsType)
{
	MapPropsData::iterator iter = m_mapPropsData.find(nPropsType);
	if (iter != m_mapPropsData.end())
	{
		return iter->second;
	}

	return 0;
}

void CPlayerAccount::AddPlayerAccountMoney(int nAccountMoney)
{
	m_nAccount += nAccountMoney;
}

void CPlayerAccount::PayPlayerAccountMoney(int nAccountMoney)
{
	m_nAccount -= nAccountMoney;
    if (m_nAccount < 0)
    {
        m_nAccount = 0;
    }
}

void CPlayerAccount::AddPlayerAccountProps(int nPropsType, int nPropsNum)
{
    MapPropsData::iterator iter = m_mapPropsData.find(nPropsType);
    if (iter != m_mapPropsData.end())
    {
        iter->second += nPropsNum;
        if (iter->second > 9999)
        {
            iter->second = 9999;
        }
    }
    else
    {
        m_mapPropsData[nPropsType] = nPropsNum;
    }
}

void CPlayerAccount::RecordPlayerScore(std::string szPlayerName, int score)
{
    if (szPlayerName.empty())
    {
        return;
    }
    
    RankingData newRank;
    memcpy(newRank.szName, szPlayerName.c_str(), strlen(szPlayerName.c_str()) );
    newRank.nScore = score;

    std::list<RankingData>::iterator iter = m_listRankData.begin();
    for (;iter != m_listRankData.end(); ++iter)
    {
        RankingData rank = *iter;
        if (rank.nScore < score)
        {
            if (m_listRankData.size() >= 10)
            {
                m_listRankData.pop_back();
            }

            m_listRankData.insert(iter, newRank);
        }   
    }
}

void CPlayerAccount::Save()
{
    char szAccountData[MAX_FILE_DATA] = {0};
    int nPropsCount = m_mapPropsData.size();
    int nFileSeek = 0;
    memcpy(szAccountData + nFileSeek, &nPropsCount, sizeof(nPropsCount));
    nFileSeek += sizeof(nPropsCount);

    MapPropsData::iterator iter = m_mapPropsData.begin();
    for (; iter != m_mapPropsData.end(); ++iter)
    {
        int nPropsData = iter->first * 10000 + iter->second;
        memcpy(szAccountData + nFileSeek, &nPropsData, sizeof(nPropsData));
        nFileSeek += sizeof(nPropsData);
    }
    
    memcpy(szAccountData + nFileSeek, &m_nAccount, sizeof(m_nAccount));
    nFileSeek += sizeof(m_nAccount);

    std::string  szAccountPath = CCFileUtils::sharedFileUtils()->getWritablePath();
    szAccountPath.append(AccountFile);

    // 如果文件不存在则创建文件
    FILE *pFile = fopen(szAccountPath.c_str(), "wb");
    fwrite(szAccountData,1, nFileSeek, pFile);
    fclose(pFile);

    if (NULL == CCUserDefault::sharedUserDefault())
    {
        return; 
    }

    std::list<RankingData>::iterator rankIter = m_listRankData.begin();
    int i = 0;
    for (; rankIter != m_listRankData.end(); ++rankIter, ++i)
    {
        std::string Namekey = Rank_Name_0;
        Namekey.append(1, i + 48);     
        std::string ScoreKey = Rank_Score_0;
        ScoreKey.append(1, i + 48);

        std::string szNameValue = (*rankIter).szName;
        CCUserDefault::sharedUserDefault()->setStringForKey(Namekey.c_str(), szNameValue);
        CCUserDefault::sharedUserDefault()->setIntegerForKey(ScoreKey.c_str(), (*rankIter).nScore);
    }
}

void CPlayerAccount::ReloadAccount()
{
    std::string  szAccountPath = CCFileUtils::sharedFileUtils()->getWritablePath();
    szAccountPath.append(AccountFile);

    FILE *pFile = fopen(szAccountPath.c_str(), "rb");
    if (NULL == pFile)
    {
        Save();
        fclose(pFile);
        return;
    }

    // 金钱, 道具数据
    char *szFileData = new char[MAX_FILE_DATA];
    int nFileLen = MAX_FILE_DATA;
    if ( EOF == fread(szFileData, 1, nFileLen, pFile))
    {
        delete []szFileData;
        fclose(pFile);
        return;
    }

    char *pTmp = szFileData;
    int nPropsCount = *((int*)pTmp);
    pTmp += sizeof(int);

    for (int i = 0; i < nPropsCount; ++i)
    {
        int nProps = *((int *)pTmp);
        pTmp += sizeof(int);

        int nPropsType = nProps/10000;
        int nPropsNum  = nProps%10000;

        m_mapPropsData[nPropsType] = nPropsNum;
    }

    m_nAccount = *((int*)pTmp);
    pTmp += sizeof(m_nAccount);
   
    delete []szFileData;
    fclose(pFile);

    // 排行榜数据
//     std::string szRankData = CCUserDefault::sharedUserDefault()->getStringForKey(Data_Rank_Key);
//     if (szRankData.empty())
//     {
//         return;
//     }
// 
//     char *pStr = szRankData.c_str();
//     int nRankCount = *((int *)pStr);
// 
//     for (int i = 0; i < nRankCount; ++i)
//     {
// 
//         RankingData *pRank = (RankingData *)pStr;
//         pStr += sizeof(RankingData);
// 
//         RankingData sRank;
//         memcpy(sRank.szName, pRank->szName, strlen(pRank->szName));
//         sRank.nScore = pRank->nScore;
// 
//         m_listRankData.push_back(sRank);
//     }
//     

    if (NULL == CCUserDefault::sharedUserDefault())
    {
        return;
    }

    int nRankCount = 10;
    m_listRankData.clear();
    for (int i = 0; i < nRankCount; ++i)
    {
        std::string Namekey = Rank_Name_0;
        Namekey.append(1, i + 48);     
        std::string ScoreKey = Rank_Score_0;
        ScoreKey.append(1, i + 48);

        RankingData sRankData;
        std::string szName = CCUserDefault::sharedUserDefault()->getStringForKey(Namekey.c_str());
        memcpy(sRankData.szName, szName.c_str(), strlen(szName.c_str()));
        sRankData.nScore = CCUserDefault::sharedUserDefault()->getIntegerForKey(ScoreKey.c_str());
        m_listRankData.push_back(sRankData);
    }
}

