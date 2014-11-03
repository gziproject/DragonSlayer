#include "GameStage.h"
#include "GameObject.h"
#include "ObjectFactory.h"
#include "GLES-Render.h"

USING_NS_CC;

CGameStage::CGameStage(void)
{
    for (int i = 0; i < 16; ++i)
    {
        m_willDestroyBullets[i] = NULL;
    }

    m_pRole = NULL;
}

CGameStage::~CGameStage(void)
{
}


CCScene* CGameStage::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();

    // 'layer' is an autorelease object
    CGameStage *layer = CGameStage::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool CGameStage::init()
{
    CCLayer::init();

    b2Vec2 gravity;
    gravity.Set(0.0f, -10.0f);
    m_b2World = new b2World(gravity);
    m_b2World->SetContactListener(this);

    GLESDebugDraw *m_debugDraw = new GLESDebugDraw( PTM_RATIO );
    m_debugDraw->SetFlags(b2Draw::e_shapeBit);
    m_b2World->SetDebugDraw(m_debugDraw);

    // 批处理节点, 用于加载斧子
    m_pSpriteBatchNode = CCSpriteBatchNode::create("images/00_01.png", 10);
    addChild(m_pSpriteBatchNode);

    return true;
}

void CGameStage::onEnter()
{
    CCLayer::onEnter();
    setAccelerometerEnabled(true);

    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -1, true);

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    
    InitFloor();

    //读取配置(如果有的话)
    //通过配置添加游戏对象
    m_pRole = AddBody(ROLEID_HERO, visibleSize.width/2, visibleSize.height/2);
    if (NULL != m_pRole)
    {
        m_pRole->getAnimation()->playWithIndex(0);
    }

    scheduleUpdate();
}

void CGameStage::onExit()
{
    CCLayer::onExit();
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

void CGameStage::update(float delta)
{
    m_b2World->Step(delta, 8, 3);
}

void CGameStage::draw()
{
    CCLayer::draw();

    ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
    kmGLPushMatrix();
    m_b2World->DrawDebugData();
    kmGLPopMatrix();
}

CGameObject* CGameStage::AddBody(int rid, float x, float y)
{
    CGameObject *pObj = CObjectFactory::GetInstance()->CreateObject(rid);
    if (NULL != pObj)
    {
        float tempW = pObj->GetB2Width();
        float tempH = pObj->GetB2Height();

        b2BodyDef bodydef;
        bodydef.type = b2_dynamicBody;
        bodydef.position.Set(x/PTM_RATIO, y/PTM_RATIO);
        bodydef.fixedRotation = true;

        b2Body *pBody = m_b2World->CreateBody(&bodydef);

        b2PolygonShape shape;
        shape.SetAsBox(tempW/2, tempH/2);
        b2FixtureDef fixdef;
        fixdef.shape = &shape;
        fixdef.density = 1.0f;
        //fixdef.userData = pObj;
        //fixdef.isSensor = true;
        pBody->CreateFixture(&fixdef);
        pBody->SetUserData(pObj);

        pObj->SetB2body(pBody);
        pObj->setPosition(x, y);
        addChild(pObj);
    }

    return pObj;
}

CPhysicsObject *CGameStage::AddAxe(int rid, float x, float y)
{
    CPhysicsObject *pObj = CObjectFactory::GetInstance()->CreateAxe(rid);
    if (NULL != pObj)
    {
        float tempRadius = pObj->GetB2Radius();

        b2BodyDef bodydef;
        bodydef.type = b2_dynamicBody;
        bodydef.position.Set(x/PTM_RATIO, y/PTM_RATIO);

        b2Body *pBody = m_b2World->CreateBody(&bodydef);

        b2CircleShape shape;
        shape.m_radius = tempRadius;
        b2FixtureDef fixdef;
        fixdef.shape = &shape;
        fixdef.density = 1.0f;
        //fixdef.userData = pObj;
        //fixdef.isSensor = true;
        pBody->CreateFixture(&fixdef);
        pBody->SetUserData(pObj);

        pObj->SetB2body(pBody);
        pObj->setPosition(ccp(x, y));
        pObj->initWithTexture(m_pSpriteBatchNode->getTexture());
        m_pSpriteBatchNode->addChild(pObj);
    }

    return pObj;
}

void CGameStage::BeginContact(b2Contact* contact)
{
    b2Body *pBody1 = contact->GetFixtureA()->GetBody();
    b2Body *pBody2 = contact->GetFixtureB()->GetBody();

    CGameObject *pObj1 = (CGameObject*)pBody1->GetUserData();
    CGameObject *pObj2 = (CGameObject*)pBody2->GetUserData();
// 
//     if (pObj1->GetRoleType() == ROLETYPE_BULLET && pObj2->GetRoleType() == ROLETYPE_MONSTER ||
//         (pObj1->GetRoleType() == ROLETYPE_MONSTER && pObj2->GetRoleType() == ROLETYPE_BULLET))
//     {
// 
//     }
}

void CGameStage::EndContact(b2Contact* contact)
{

}

void CGameStage::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{

}

void CGameStage::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{

}

bool CGameStage::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    CCSize visibleSize = CCDirector::sharedDirector()->getWinSize();
    CCPoint pos = pTouch->getLocation();

    //AddTestBoxAtPos(pos.x, pos.y);

    //CGameObject *obj = AddBody(ROLEID_HERO, pos.x, pos.y);
//     CGameObject *obj = AddBody(ROLEID_MONSTER, pos.x, pos.y);
//     if (obj!=NULL)
//     {
//         obj->getAnimation()->playWithIndex(0);
//     }

    AddAxe(ROLEID_NORMAXE, pos.x, pos.y);

    if (pos.x > visibleSize.width/2)
    {
        ApplyLeftForce(2000.0f);
    }
    else
    {
        ApplyRightForce(2000.0f);
    }

    return true;
}

void CGameStage::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{

}

void CGameStage::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{

}

void CGameStage::didAccelerate(cocos2d::CCAcceleration* pAccelerationValue)
{
    double &x = pAccelerationValue->x;
    double &y = pAccelerationValue->y;


}

void CGameStage::InitFloor()
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0, 0); // bottom-left corner

    b2Body* groundBody = m_b2World->CreateBody(&groundBodyDef);
    b2EdgeShape groundBox;

    // bottom
    groundBox.Set(b2Vec2(0/PTM_RATIO, 0/PTM_RATIO), b2Vec2(visibleSize.width/PTM_RATIO , 0/PTM_RATIO));
    groundBody->CreateFixture(&groundBox,0);

    // top
    groundBox.Set(b2Vec2(0/PTM_RATIO, visibleSize.height/PTM_RATIO), b2Vec2(visibleSize.width/PTM_RATIO, visibleSize.height/PTM_RATIO));
    groundBody->CreateFixture(&groundBox,0);

    // left
    groundBox.Set(b2Vec2(0/PTM_RATIO, visibleSize.height/PTM_RATIO), b2Vec2(0/PTM_RATIO, 0/PTM_RATIO));
    groundBody->CreateFixture(&groundBox,0);

    // right
    groundBox.Set(b2Vec2(visibleSize.width/PTM_RATIO, 0/PTM_RATIO), b2Vec2(visibleSize.width/PTM_RATIO, visibleSize.height/PTM_RATIO));
    groundBody->CreateFixture(&groundBox,0);
}

void CGameStage::AddTestBoxAtPos(float x, float y)
{
    b2BodyDef bodydef;
    bodydef.type = b2_dynamicBody;
    bodydef.position.Set(x/PTM_RATIO, y/PTM_RATIO);

    b2Body *pBox = m_b2World->CreateBody(&bodydef);
    b2PolygonShape shape;
    shape.SetAsBox(0.5f, 0.5f);
    b2FixtureDef fdef;
    fdef.shape = &shape;
    fdef.density = 1.0f;

    pBox->CreateFixture(&fdef);
}

void CGameStage::ApplyLeftForce(float fForce)
{
    ApplyRightForce(-1 * fForce);
}

void CGameStage::ApplyRightForce(float fForce)
{
    b2Body *pPlayerBody = m_pRole->GetB2body();
    b2Vec2 f = pPlayerBody->GetWorldVector(b2Vec2(fForce, 0.0f));
    pPlayerBody->ApplyForceToCenter(f);
}
