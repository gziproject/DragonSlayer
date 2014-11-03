#include "PhysicsObject.h"

USING_NS_CC;

#define PTM_RATIO 32

CPhysicsObject::CPhysicsObject(void)
{
    m_pB2body = NULL;
}

CPhysicsObject::~CPhysicsObject(void)
{
}

bool CPhysicsObject::init()
{
    return true;
}

void CPhysicsObject::onEnter()
{
    CCSprite::onEnter();

}

void CPhysicsObject::onExit()
{
    CCSprite::onExit();

}

bool CPhysicsObject::isDirty(void)
{
    return true;
}

CCAffineTransform CPhysicsObject::nodeToParentTransform()
{
    b2Vec2 pos  = m_pB2body->GetPosition();

    float x = pos.x * PTM_RATIO;
    float y = pos.y * PTM_RATIO;

    if ( isIgnoreAnchorPointForPosition() ) {
        x += m_obAnchorPointInPoints.x;
        y += m_obAnchorPointInPoints.y;
    }

    // Make matrix
    float radians = m_pB2body->GetAngle();
    float c = cosf(radians);
    float s = sinf(radians);

    if( ! m_obAnchorPointInPoints.equals(CCPointZero) ){
        x += c*-m_obAnchorPointInPoints.x + -s*-m_obAnchorPointInPoints.y;
        y += s*-m_obAnchorPointInPoints.x + c*-m_obAnchorPointInPoints.y;
    }

    // Rot, Translate Matrix
    m_sTransform = CCAffineTransformMake( c,  s,
        -s,    c,
        x,    y );

    return m_sTransform;
}
