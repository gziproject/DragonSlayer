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
    CCSprite::nodeToParentTransform();

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

    bool needsSkewMatrix = ( m_fSkewX || m_fSkewY );

    if(!m_obAnchorPointInPoints.equals(CCPointZero) ){
        x += c*-m_obAnchorPointInPoints.x * m_fScaleX + -s*-m_obAnchorPointInPoints.y*m_fScaleX;
        y += s*-m_obAnchorPointInPoints.x * m_fScaleY + c*-m_obAnchorPointInPoints.y*m_fScaleY;
    }

    // Rot, Translate Matrix
    m_sTransform = CCAffineTransformMake( c * m_fScaleX,  s * m_fScaleX,
        -s * m_fScaleY,  c * m_fScaleY,
        x,    y );

    if (needsSkewMatrix) 
    {
        CCAffineTransform skewMatrix = CCAffineTransformMake(1.0f, tanf(CC_DEGREES_TO_RADIANS(m_fSkewY)),
            tanf(CC_DEGREES_TO_RADIANS(m_fSkewX)), 1.0f,
            0.0f, 0.0f );
        m_sTransform = CCAffineTransformConcat(skewMatrix, m_sTransform);

        // adjust anchor point
        if (!m_obAnchorPointInPoints.equals(CCPointZero))
        {
            m_sTransform = CCAffineTransformTranslate(m_sTransform, -m_obAnchorPointInPoints.x, -m_obAnchorPointInPoints.y);
        }
    }

    if (m_bAdditionalTransformDirty)
    {
        m_sTransform = CCAffineTransformConcat(m_sTransform, m_sAdditionalTransform);
        m_bAdditionalTransformDirty = false;
    }

    return m_sTransform;
}
