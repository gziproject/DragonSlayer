
#ifndef __PLAYER_ACCOUNT_H__
#define __PLAYER_ACCOUNT_H__

#include <map>
#include <list>

#define         NAME_LENGTH         32 

struct RankingData
{
    char            szName[NAME_LENGTH];
    int             nScore;
};

class CPlayerAccount
{
	typedef std::map<int, int> MapPropsData;        // <nPropsType, PropsNum>

private:
	CPlayerAccount();
	~CPlayerAccount();

public:

	static CPlayerAccount *GetAccountInstance();
	static void DestroyAccountInstance();

public:
	
	int	 GetAccountsMoney();
	int  GetAccountPropsNum(int nPropsType);

    // 钱数, 递增
	void AddPlayerAccountMoney(int nAccountMoney);
    // 钱数, 递减
	void PayPlayerAccountMoney(int nAccountMoney);
    // 道具, 递增递减
	void AddPlayerAccountProps(int nPropsType, int nPropsNum);

    void RecordPlayerScore(std::string szPlayerName, int score);

	void Save();

	void ReloadAccount();

private:
	
    static CPlayerAccount		*m_pAccountInstance;
    int							m_nAccount;
    MapPropsData				m_mapPropsData;
    std::list<RankingData>      m_listRankData;
};

#endif //__PLAYER_ACCOUNT_H__
