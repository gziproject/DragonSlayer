
#ifndef __ARMATURELOADER_H__
#define __ARMATURELOADER_H__

#include <map>
#include <list>
#include <string>

namespace cocos2d
{
    namespace extension
    {
        class CCArmature;
    }
}

class ArmatureLoader
{
public:
    ArmatureLoader(void);
    ~ArmatureLoader(void);

public:

    static ArmatureLoader* GetInstance();
    static void Destroy();

    // ����һ�������ļ�, ͨ�������ļ���Ϣ�������й�������
    bool LoadArmatureWithFile(const char *szFile);

    // ͨ��id��֮ƥ�����Ϣ����һ������
    cocos2d::extension::CCArmature *CreateArmature(int armid);

    // ���ָ��id�Ķ�Ӧ�����ļ���
    std::string GetArmatureName(int armid);

private:

    static ArmatureLoader       *m_Instance;
    std::map<int, std::string>  m_ArmaRes;
    std::list<std::string>      m_LoadFiles;
};

#endif //__ARMATURELOADER_H__
