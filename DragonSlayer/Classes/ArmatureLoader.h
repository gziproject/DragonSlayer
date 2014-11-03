
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

    // 加载一个管理文件, 通过管理文件信息加载所有骨骼动画
    bool LoadArmatureWithFile(const char *szFile);

    // 通过id与之匹配的信息创建一个盔甲
    cocos2d::extension::CCArmature *CreateArmature(int armid);

    // 获得指定id的对应骨骼文件名
    std::string GetArmatureName(int armid);

private:

    static ArmatureLoader       *m_Instance;
    std::map<int, std::string>  m_ArmaRes;
    std::list<std::string>      m_LoadFiles;
};

#endif //__ARMATURELOADER_H__
