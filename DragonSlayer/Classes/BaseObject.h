#ifndef __BASEOBJECT_H__
#define __BASEOBJECT_H__

#include "DGameDef.h"

class CBaseObject
{
public:
    CBaseObject(void);
    virtual ~CBaseObject(void);

    // 角色类型
    virtual int GetRoleType() { return ROLETYPE_NONE; }
    
    // 角色ID
    virtual void SetRoleID(int rid) { m_nRoleID = rid; }
    virtual int GetRoleID() { return m_nRoleID; }

    virtual bool IsTouchGroundRemove() { return false; }

protected:

    int         m_nRoleID;  //角色id
};

#endif // __BASEOBJECT_H__
