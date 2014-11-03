#ifndef __GAMESTAGE_H__
#define __GAMESTAGE_H__

#include "cocos2d.h"
#include "GameObject.h"
#include "PhysicsObject.h"
#include "Box2D/Box2D.h"

class CGameStage : 
    public cocos2d::CCLayer,
    public b2ContactListener
{
public:
    CGameStage(void);
    ~CGameStage(void);

public:

    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    virtual void update(float delta);
    virtual void draw();

    CREATE_FUNC(CGameStage);
    // ��������
    static cocos2d::CCScene* scene();
    // ���һ�����嵽��Ϸ��������
    CGameObject* AddBody(int rid, float x, float y);
    CPhysicsObject *AddAxe(int rid, float x, float y);
    // ������ײ
    virtual void BeginContact(b2Contact* contact);
    virtual void EndContact(b2Contact* contact);

    virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
    virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);

    // ������
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

    // ��������
    virtual void didAccelerate(cocos2d::CCAcceleration* pAccelerationValue);

private:

    void InitFloor();

    void AddTestBoxAtPos(float x, float y);

    void ApplyLeftForce(float fForce);

    void ApplyRightForce(float fForce);

private:

    b2World             *m_b2World;                     // ��Ϸ��������
    b2Body              *m_willDestroyBullets[16];      

    CGameObject         *m_pRole;                       // ��Ϸ��ɫ
    cocos2d::CCSpriteBatchNode   *m_pSpriteBatchNode;            // ������ڵ�
};

#endif // __GAMESTAGE_H__

