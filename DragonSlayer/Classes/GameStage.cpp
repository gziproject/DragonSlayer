#include "GameStage.h"
#include "GameObject.h"
#include "ObjectFactory.h"
#include "GLES-Render.h"
#include "Axe.h"
#include "Role.h"
#include "Monster.h"
#include "DGameDef.h"
#include "GameUILayer.h"

USING_NS_CC;
using namespace std;

CGameStage::CGameStage(void)
{
    for (int i = 0; i < 32; ++i)
    {
        m_willDestroyBodys[i] = NULL;
    }

    m_pRole = NULL;
    m_nBodyIndex = -1;
    m_nPoints = 0;
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
    // ������ڵ�, ���ڼ��ظ���
    m_pSpriteBatchNode = CCSpriteBatchNode::create("images/00_01.png", 10);
    addChild(m_pSpriteBatchNode, 1);

    return true;
}

void CGameStage::onEnter()
{
    CCLayer::onEnter();
    setAccelerometerEnabled(true);

    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -1, true);
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

    InitFloor();

    //��ȡ����(����еĻ�)
    //ͨ�����������Ϸ����
    m_pRole = dynamic_cast<CRole*>(AddBody(ROLEID_HERO, visibleSize.width/2 + 100, visibleSize.height/2));
    if (NULL != m_pRole)
    {
        m_pRole->getAnimation()->playWithIndex(0);
    }

    CGameObject *pTestMons = AddBody(ROLEID_MONSTER, visibleSize.width/2+100, visibleSize.height/2+ 100 );
    if (NULL != pTestMons)
    {
        pTestMons->getAnimation()->playWithIndex(0);
    }

    //ע����Ϣ
    CCNotificationCenter::sharedNotificationCenter()->addObserver(
        this, callfuncO_selector(CGameStage::onAttackCallback), MSG_ROLEACOMPLETE, NULL);

    scheduleUpdate();
}

void CGameStage::onExit()
{
    CCLayer::onExit();
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, MSG_ROLEACOMPLETE);
}

void CGameStage::update(float delta)
{
    m_b2World->Step(delta, 8, 3);

    for (int32 i = 0; i < m_nPoints; ++i)
    {
        SContactPoint* point = m_ContactPoints + i;

        b2Body* pBody1 = point->fixtureA->GetBody();
        b2Body* pBody2 = point->fixtureB->GetBody();
        CBaseObject *pObj1 = reinterpret_cast<CBaseObject*>(pBody1->GetUserData());
        CBaseObject *pObj2 = reinterpret_cast<CBaseObject*>(pBody2->GetUserData());

        CAxe *pAxe = NULL;
        CMonster *pMonster = NULL;

        // �����ذ��, ����Ӣ���Լ�, ����ʲô������ɾ��
        if (pObj1 == NULL && pObj2->GetRoleType() != ROLETYPE_HERO)
        {
            m_willDestroyBodys[++m_nBodyIndex] = pBody2;
            CCNode* pRm = dynamic_cast<CCNode*>(pObj2);
            pRm->removeFromParentAndCleanup(true);

        }
        else if (pObj2 == NULL && pObj1->GetRoleType() != ROLETYPE_HERO)
        {
            m_willDestroyBodys[++m_nBodyIndex] = pBody1;
            CCNode* pRm = dynamic_cast<CCNode*>(pObj1);
            pRm->removeFromParentAndCleanup(true);
        }
        else if (pObj1 && pObj1->GetRoleType() == ROLETYPE_AXE && 
            pObj2 && pObj2->GetRoleType() == ROLETYPE_MONSTER)
        {
            pAxe = dynamic_cast<CAxe*>(pObj1);
            pMonster = dynamic_cast<CMonster*>(pObj2);
            pMonster->Injure(pAxe->GetPower());

            m_ReleaseList.insert(pAxe);
            m_willDestroyBodys[++m_nBodyIndex] = pBody1;
        }
        else if (pObj2 && pObj2->GetRoleType() == ROLETYPE_AXE 
            && pObj1 && pObj1->GetRoleType() == ROLETYPE_MONSTER)
        {
            pAxe = dynamic_cast<CAxe*>(pObj2);
            pMonster = dynamic_cast<CMonster*>(pObj1);
            pMonster->Injure(pAxe->GetPower());

            m_ReleaseList.insert(pAxe);
            m_willDestroyBodys[++m_nBodyIndex] = pBody2;
        }
    }

    int count = m_nBodyIndex + 1;
    std::sort(m_willDestroyBodys, m_willDestroyBodys + count);

    if (m_nBodyIndex >= 0)
    {
        while (m_nBodyIndex >= 0)
        {
            b2Body *pWillDes = m_willDestroyBodys[m_nBodyIndex--];
            while (m_nBodyIndex > -1  && m_willDestroyBodys[m_nBodyIndex] == pWillDes)
            {
                --m_nBodyIndex;
            }

            m_b2World->DestroyBody(pWillDes);
        }
    }

    for (set<CPhysicsObject *>::iterator iter = m_ReleaseList.begin(); 
        iter != m_ReleaseList.end(); ++iter)
    {
        CAxe *pAxe = dynamic_cast<CAxe*>(*iter);
        pAxe->RemoveSelf();
    }

    m_nPoints = 0;
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
        //fixdef.filter.groupIndex = 1;
        if(rid == ROLEID_HERO)
        {
            fixdef.filter.categoryBits = COLLIDE_CATEGORY_ROLE;
            fixdef.filter.maskBits = COLLIDE_MASKBIT_ROLE;
        }
        else
        {
            fixdef.filter.categoryBits = COLLIDE_CATEGORY_MONSTER;
            fixdef.filter.maskBits = COLLIDE_MASKBIT_MONSTER;
        }

        pBody->CreateFixture(&fixdef);
        pBody->SetUserData((CBaseObject*)pObj);

        if (rid != ROLEID_HERO)
        {
            // ������һ���ĸ߶ȴ�������, ������������
            b2PrismaticJointDef pjd;
            b2Vec2 axis(1.0f, 0.0f);
            axis.Normalize();
            pjd.Initialize(m_groundBody, pBody, b2Vec2(1.0f, 0.0f), axis);
            pjd.motorSpeed = -1.0f;
            pjd.maxMotorForce = 1000.0f;
            pjd.enableMotor = true;
            pjd.lowerTranslation = 0.0f;
            pjd.upperTranslation = 20.0f;
            pjd.enableLimit = false;

            b2PrismaticJoint *pJoint = dynamic_cast<b2PrismaticJoint *>(m_b2World->CreateJoint(&pjd));
        }

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
        //fixdef.filter.groupIndex = 1;
        if(rid == ROLEID_MONSHIT)
        {
            fixdef.filter.categoryBits = COLLIDE_CATEGORY_MONSTER;
            fixdef.filter.maskBits = COLLIDE_MASKBIT_MONSTER;
        }
        else
        {
            fixdef.filter.categoryBits = COLLIDE_CATEGORY_ROLE;
            fixdef.filter.maskBits = COLLIDE_MASKBIT_ROLE;
        }

        pBody->CreateFixture(&fixdef);
        pBody->SetUserData((CBaseObject*)pObj);
        // ʩ����ת����
        pBody->ApplyAngularImpulse(1.0f);

        pObj->SetB2body(pBody);
        pObj->setPosition(ccp(x, y));
        pObj->initWithTexture(m_pSpriteBatchNode->getTexture());
        m_pSpriteBatchNode->addChild(pObj);
    }

    return pObj;
}

void CGameStage::BeginContact(b2Contact* contact)
{

}

void CGameStage::EndContact(b2Contact* contact)
{

}

void CGameStage::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
    const b2Manifold* manifold = contact->GetManifold();

    if (manifold->pointCount == 0)
    {
        return;
    }

    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();

    b2PointState state1[b2_maxManifoldPoints], state2[b2_maxManifoldPoints];
    b2GetPointStates(state1, state2, oldManifold, manifold);

    b2WorldManifold worldManifold;
    contact->GetWorldManifold(&worldManifold);

    for (int32 i = 0; i < manifold->pointCount; ++i)
    {
        SContactPoint* cp = m_ContactPoints + m_nPoints;
        cp->fixtureA = fixtureA;
        cp->fixtureB = fixtureB;
        cp->position = worldManifold.points[i];
        cp->normal = worldManifold.normal;
        cp->state = state2[i];
        ++m_nPoints;
    }
}

void CGameStage::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{

}

bool CGameStage::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    CCSize visibleSize = CCDirector::sharedDirector()->getWinSize();
    CCPoint pos = pTouch->getLocation();

    // �Ƿ���Ҫ��������
    if (m_pRole->IsReload())
    {
        OnAttackMonster();
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


    //     if (pos.x > visibleSize.width/2)
    //     {
    //         ApplyLeftForce(2000.0f);
    //     }
    //     else
    //     {
    //         ApplyRightForce(2000.0f);
    //     }
}

void CGameStage::InitFloor()
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0, 0); // bottom-left corner

    m_groundBody = m_b2World->CreateBody(&groundBodyDef);
    b2EdgeShape groundBox;

    float height = visibleSize.height * 2;
    float width = visibleSize.width * 2;

    // bottom
    groundBox.Set(b2Vec2((-1*width/2)/PTM_RATIO, 0/PTM_RATIO), b2Vec2(width+(-1*width/2)/PTM_RATIO , 0/PTM_RATIO));
    m_groundBody->CreateFixture(&groundBox,0);

    // top
    groundBox.Set(b2Vec2((-1*width/2)/PTM_RATIO, height/PTM_RATIO), b2Vec2(width +(-1*width/2)/PTM_RATIO, height/PTM_RATIO));
    m_groundBody->CreateFixture(&groundBox,0);

    // left
    groundBox.Set(b2Vec2((-1*width/2)/PTM_RATIO, height/PTM_RATIO), b2Vec2((-1*width/2)/PTM_RATIO, 0/PTM_RATIO));
    m_groundBody->CreateFixture(&groundBox,0);

    // right
    groundBox.Set(b2Vec2(width+ (-1*width/2)/PTM_RATIO, 0/PTM_RATIO), b2Vec2(width+(-1*width/2)/PTM_RATIO, height/PTM_RATIO));
    m_groundBody->CreateFixture(&groundBox,0);
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

void CGameStage::OnAttackMonster()
{
    m_pRole->ThrowAxe();
}

void CGameStage::onAttackCallback(cocos2d::CCObject *pObj)
{
    // ��ýǶ�, ����, ���丫ͷ
    float angles = 0.0f;
    float power = 0.0f;
    float x = m_pRole->getPositionX() + 50;
    float y = m_pRole->getPositionY();

    b2Vec2 v2Force = b2Vec2(-200.0f, 700.0f);
    CPhysicsObject *pAxe = AddAxe(ROLEID_NORMAXE, x, y);
    if (NULL != pAxe)
    {
        b2Body *pBody = pAxe->GetB2body();
        pBody->ApplyForce(v2Force, pBody->GetPosition());
    }
}