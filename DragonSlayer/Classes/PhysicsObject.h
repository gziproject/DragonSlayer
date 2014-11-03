#ifndef __PHYSICOBJECT_H__
#define __PHYSICOBJECT_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "BaseObject.h"

class CPhysicsObject :
    public cocos2d::CCSprite,
    public CBaseObject
{
public:
    CPhysicsObject(void);
    virtual ~CPhysicsObject(void);

public: 

    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    virtual bool isDirty();
    virtual cocos2d::CCAffineTransform nodeToParentTransform();

    virtual void SetB2body(b2Body *pB2body) { m_pB2body = pB2body; }
    virtual b2Body *GetB2body() { return m_pB2body; }
    virtual float GetB2Radius() { return m_fB2Radius;}

protected:

    b2Body      *m_pB2body;
    float       m_fB2Radius;
};

#endif //__PHYSICOBJECT_H__
