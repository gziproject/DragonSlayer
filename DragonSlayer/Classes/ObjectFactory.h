#ifndef __OBJECTFACTORY_H__
#define __OBJECTFACTORY_H__

#include "GameObject.h"
#include "PhysicsObject.h"

class CObjectFactory
{
private:
    CObjectFactory(void);
    ~CObjectFactory(void);

public:

    static CObjectFactory *GetInstance();
    static void Destroy();

    CGameObject *CreateObject(int rid);

    CPhysicsObject *CreateAxe(int rid);
    
private:    

    static CObjectFactory   *m_Instance;
};

#endif //__OBJECTFACTORY_H__
