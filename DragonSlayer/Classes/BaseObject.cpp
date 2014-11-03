#include "BaseObject.h"
#include "DGameDef.h"


CBaseObject::CBaseObject(void)
{
}

CBaseObject::~CBaseObject(void)
{
}

int CBaseObject::GetRoleType()
{
    return ROLETYPE_NONE;
}

int CBaseObject::GetRoleID()
{
    return m_nRoleID;
}