#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include "cocos-ext.h"
#include "DGameDef.h"
#include "Box2D/Box2D.h"
#include "BaseObject.h"

// �ö���Ҳ���������, ���ǲ�������Ƕȸ���, ��������ģ��, ʹ�ù̶��Ĺ��򷽿�

class CGameObject : 
    public cocos2d::extension::CCArmature, 
    public CBaseObject
{
public:
    CGameObject(void);
    virtual ~CGameObject(void);

public:
    // ʵ����һ������
    static CGameObject* create(int rid);
    // ���ø���
    virtual void SetB2body(b2Body *body) { m_pB2body = body; }
    // ��ø���
    virtual b2Body *GetB2body() { return m_pB2body; }
    // ͨ�����ֲ��Ŷ���
    virtual void PlayAction(const char *szActionName, int durationTo = -1, int durationTween = -1,  int loop = -1, int tweenEasing = 10000);
    // ���ݹ��������ߴ�ת������������Ĵ�С
    virtual float GetB2Width();
    virtual float GetB2Height();

    virtual void onEnter();
    virtual void onExit();
    virtual void update(float dt);

protected:

    float         m_fB2Width;
    float         m_fB2Height;
    float         m_fBlood;
    b2Body        *m_pB2body;   
    
};

#endif //__GAMEOBJECT_H__
