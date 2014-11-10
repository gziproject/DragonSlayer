
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

    // ����csv�ļ�
    bool            LoadFile(const char *szFilePath);

    // ���ĳ������
    bool            GetLineValue(CSVLINE &csvLine, int nLine);

    // ������
    int             GetFileLines();

    // ����ѷָ���sep�ָ�����ַ�����
    void            GetStringFromString(const std::string &str, std::vector<std::string> &values, char sep = '+');

    // ��÷ָ���sep�ָ���������
    void            GetIntFromString(const std::string &str, std::vector<int> &values, char sep = '+');

    // ��÷ָ���sep�ָ��ĸ�������
    void            GetFloatFromString(const std::string &str, std::vector<float> &values, char sep = '+');

private:

    CSVTABLE                m_table;                // csv table
};

#endif // __CSV_LOADER_H__
