/************************************************************************/
/* ���������, ������Ϸʱ, ���ڳ�ʼ������, ���ù���, �Լ���Ϸ����ʱ���������Ϣ      */
/*                                                                       */
/************************************************************************/

#ifndef __MONSTER_MANAGER_H__
#define __MONSTER_MANAGER_H__

#include "cocos2d.h"
#include <list>

class CMonsterManager
{
public:
    CMonsterManager(void);
    ~CMonsterManager(void);

public:

    // ������Ϸʱ, ���ù�����Ϣ
    bool InitMonsterMrg();

    // ������Ϸ, ���������Ϣ
    bool UninitMonsterMrg();

    // ������Ϸ����
    void SetMonsterScene(cocos2d::CCLayer *pLayer);

    // ��ѯ������
    void UpdateMonsterMrg(float dt);
    
private:
    
    cocos2d::CCLayer                     *m_GameScene;       //��Ϸ����
    std::list<cocos2d::CCObject *>       m_MonsterList;      //�����б�
};

#endif //__MONSTER_MANAGER_H__