#ifndef __BASEOBJECT_H__
#define __BASEOBJECT_H__

class CBaseObject
{
public:
    CBaseObject(void);
    virtual ~CBaseObject(void);

    // ��ɫ����
    virtual int GetRoleType();
    // ��ɫID
    virtual void SetRoleID(int rid) { m_nRoleID = rid; }
    virtual int GetRoleID();

protected:

    int         m_nRoleID;  //��ɫid
};

#endif // __BASEOBJECT_H__
