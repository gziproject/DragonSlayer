
#ifndef __CSV_LOADER_H__
#define __CSV_LOADER_H__

#include <string>
#include <vector>

typedef std::vector<std::string>     CSVLINE;
typedef std::vector<CSVLINE>         CSVTABLE;

class CCsvLoader
{
public:
    CCsvLoader();
    ~CCsvLoader();

public:

    // 加载csv文件
    bool            LoadFile(const char *szFilePath);

    // 获得某行数据
    bool            GetLineValue(CSVLINE &csvLine, int nLine);

    // 总行数
    int             GetFileLines();

    // 获得已分隔符sep分隔后的字符串集
    void            GetStringFromString(const std::string &str, std::vector<std::string> &values, char sep = '+');

    // 获得分隔符sep分割后的整数集
    void            GetIntFromString(const std::string &str, std::vector<int> &values, char sep = '+');

    // 获得分隔符sep分割后的浮点数集
    void            GetFloatFromString(const std::string &str, std::vector<float> &values, char sep = '+');

private:

    CSVTABLE                m_table;                // csv table
};

#endif // __CSV_LOADER_H__
