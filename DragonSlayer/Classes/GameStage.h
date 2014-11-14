#ifndef __GAMESTAGE_H__
#define __GAMESTAGE_H__

#include "cocos2d.h"
#include "GameObject.h"
#include "PhysicsObject.h"
#include "Box2D/Box2D.h"

#include <set>

class CRole;
// 碰撞的点
struct SContactPoint
{
    b2Fixture* fixtureA;
    b2Fixture* fixtureB;
    b2Vec2 normal;
    b2Vec2 position;
    b2PointState state;
};

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
    // 创建场景
    static cocos2d::CCScene* scene();
    // 添加一个物体到游戏场景里面
    CGameObject* AddBody(int rid, float x, float y);
    CPhysicsObject *AddAxe(int rid, float x, float y);

    // 处理碰撞
    virtual void BeginContact(b2Contact* contact);
    virtual void EndContact(b2Contact* contact);
    virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
    virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);

    // 处理点击
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

    // 处理重力
    virtual void didAccelerate(cocos2d::CCAcceleration* pAccelerationValue);

private:

    void InitFloor();
    void AddTestBoxAtPos(float x, float y);
    void ApplyMoveLeftForce(float fForce);
    void ApplyMoveRightForce(float fForce);

    // 玩家操作: 投掷斧头
    void OnAttackMonster();
    void onAttackCallback(cocos2d::CCObject *pObj);

private:

    b2World*        m_b2World;                     // 游戏物理世界
    b2Body*         m_groundBody;                  // 地板
    b2Body*         m_willDestroyBodys[32];        // 处理碰撞之后将会删除的刚体
    SContactPoint   m_ContactPoints[1024];         // 所有碰撞点
    CRole*    m_pRole;                       // 游戏控制角色
    cocos2d::CCSpriteBatchNode* m_pSpriteBatchNode;   // 批处理节点

    std::set<CPhysicsObject *> m_ReleaseList;         // 释放的列表

    int             m_nBodyIndex;                  // 需要销毁刚体列表下标
    int             m_nPoints;                     // 碰撞点个数
};

#endif // __GAMESTAGE_H__

