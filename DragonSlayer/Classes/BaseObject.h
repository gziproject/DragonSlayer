#ifndef __BASEOBJECT_H__
#define __BASEOBJECT_H__

class CBaseObject
{
public:
    CBaseObject(void);
    virtual ~CBaseObject(void);

    // 角色类型
    virtual int GetRoleType();
    // 角色ID
    virtual void SetRoleID(int rid) { m_nRoleID = rid; }
    virtual int GetRoleID();

protected:

    int         m_nRoleID;  //角色id
};

#endif // __BASEOBJECT_H__
