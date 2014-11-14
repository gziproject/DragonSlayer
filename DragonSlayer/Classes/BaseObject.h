#ifndef __BASEOBJECT_H__
#define __BASEOBJECT_H__

#include "DGameDef.h"

class CBaseObject
{
public:
    CBaseObject(void);
    virtual ~CBaseObject(void);

    // ��ɫ����
    virtual int GetRoleType() { return ROLETYPE_NONE; }
    
    // ��ɫID
    virtual void SetRoleID(int rid) { m_nRoleID = rid; }
    virtual int GetRoleID() { return m_nRoleID; }

    virtual bool IsTouchGroundRemove() { return false; }

protected:

    int         m_nRoleID;  //��ɫid
};

#endif // __BASEOBJECT_H__
