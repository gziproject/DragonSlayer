#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include "cocos-ext.h"
#include "DGameDef.h"
#include "Box2D/Box2D.h"
#include "BaseObject.h"

// 该对象也是物理对象, 但是不做物理角度更新, 骨骼不好模拟, 使用固定的规则方块

class CGameObject : 
    public cocos2d::extension::CCArmature, 
    public CBaseObject
{
public:
    CGameObject(void);
    virtual ~CGameObject(void);

public:
    // 实例化一个对象
    static CGameObject* create(int rid);
    // 设置刚体
    virtual void SetB2body(b2Body *body) { m_pB2body = body; }
    // 获得刚体
    virtual b2Body *GetB2body() { return m_pB2body; }
    // 通过名字播放动作
    virtual void PlayAction(const char *szActionName);
    // 根据骨骼动画尺寸转换成物理世界的大小
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
