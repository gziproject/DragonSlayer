#include "CsvLoader.h"
#include "cocos2d.h"

USING_NS_CC;
using namespace std;

CCsvLoader::CCsvLoader()
{
    m_table.clear();
}

CCsvLoader::~CCsvLoader()
{
    
}

bool CCsvLoader::LoadFile(const char *szCsvFilePath)
{
    if (NULL == szCsvFilePath)
    {
        return false;
    }

    unsigned long nFileSize = 0;
    unsigned char* pFileData = CCFileUtils::sharedFileUtils()->getFileData(
        CCFileUtils::sharedFileUtils()->fullPathForFilename(szCsvFilePath).c_str(), "rt", &nFileSize);

    if (0 == nFileSize)
    {
        CCLog("FileData is empty! file=%s", szCsvFilePath);
        if (NULL != pFileData)
        {
            delete pFileData;
            pFileData = NULL;
        }

        return false;
    }

    // 开始数据填充
    m_table.clear();
    
    string strFileStr((char*)pFileData, nFileSize);

    CSVLINE csvLine;
    csvLine.clear();
    GetStringFromString(strFileStr, csvLine, '\n');
    
    if (csvLine.empty())
    {
        delete pFileData;
        pFileData = NULL;
        return false;
    }

    CSVLINE csvGrid;
    for (CSVLINE::iterator iter = csvLine.begin(); iter != csvLine.end(); ++iter)
    {
        csvGrid.clear();
        GetStringFromString(*iter, csvGrid, ',');
        m_table.push_back(csvGrid);
    }


    delete pFileData;
    pFileData = NULL;
    return true;
}

bool CCsvLoader::GetLineValue(CSVLINE &csvLine, int nLine)
{
    csvLine = m_table[nLine];
    return true;
}

int  CCsvLoader::GetFileLines()
{
    return m_table.size();
}

void CCsvLoader::GetStringFromString(const string& str, std::vector<std::string> &values, char sep)
{
    if (str.empty())
    {
        return;
    }

    int pos = 0;
    int step = 0;

    while (static_cast<unsigned int>(pos) <= str.length() && step != -1)
    {
        step = str.find_first_of(sep, pos);
        string seg = str.substr(pos, step - pos);
        if (sep == '\n')
        {
            int rPos = seg.find('\r');
            if (rPos >= 0)
            {
                seg.erase(rPos, 1);
            }
        }

        values.push_back(seg);
        pos = step + 1;
    }
}

void CCsvLoader::GetIntFromString(const std::string &str, std::vector<int> &values, char sep)
{
    if (str.empty())
    {
        return;
    }

    int pos = 0;
    int step = 0;

    while (static_cast<unsigned int>(pos) <= str.length() && step != -1)
    {
        step = str.find_first_of(sep, pos);
        string seg = str.substr(pos, step - pos);
        int n2Int = atoi(seg.c_str());
        values.push_back(n2Int);
        pos = step + 1;
    }
}

void CCsvLoader::GetFloatFromString(const std::string &str, std::vector<float> &values, char sep)
{
    if (str.empty())
    {
        return;
    }

    int pos = 0;
    int step = 0;

    while (static_cast<unsigned int>(pos) <= str.length() && step != -1)
    {
        step = str.find_first_of(sep, pos);
        string seg = str.substr(pos, step - pos);
        float n2Float = static_cast<float>(atof(seg.c_str()));
        values.push_back(n2Float);
        pos = step + 1;
    }
}
