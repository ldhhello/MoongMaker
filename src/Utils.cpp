#include "Utils.h"
#include <random>
#include <fstream>

/*void Utils::wstring_to_string(const wstring& str, string& res)
{
    //res = str;
    return;
}

void Utils::string_to_wstring(const string& str, wstring& res)
{
    //res = str;
    return;
}*/

/*void Utils::wstring_to_string(const wstring& str, string& res)
{
    const wstring& strUni = str;
    int len = WideCharToMultiByte(CP_ACP, 0, &strUni[0], -1, NULL, 0, NULL, NULL);

    res.resize(len);
    WideCharToMultiByte(CP_ACP, 0, &strUni[0], -1, &res[0], len, NULL, NULL);
}

void Utils::string_to_wstring(const string& str, wstring& res)
{
    const string& strMulti = str;
    int nLen = MultiByteToWideChar(CP_ACP, 0, &strMulti[0], strMulti.size(), NULL, NULL);
    res.resize(nLen);
    MultiByteToWideChar(CP_ACP, 0, &strMulti[0], strMulti.size(), &res[0], nLen);
}*/

bool Utils::read_all_file(string& res, const string& filename)
{
    ifstream fin(filename, ios::binary);

    if (fin.fail())
        return false;

    fin.seekg(0, ios::end);
    int length = fin.tellg();
    fin.seekg(0, ios::beg);

    res.resize(length);

    fin.read(&res[0], length);

    return true;
}

void Utils::trim(string& str)
{
    int i = 0;
    while (i < str.length() && (str[i] == ' ' || str[i] == '\n' || str[i] == '\r' || str[i] == '\t' || str[i] == '\b')) i++;
    int j = str.length() - 1;
    while (j >= 0 && (str[j] == ' ' || str[j] == '\n' || str[j] == '\r' || str[j] == '\t' || str[i] == '\b')) j--;

    //return str.substr(i, j - i + 1);

    //str.resize(j+1);
    str.erase(j + 1);
    str.erase(0, i);
}

void Utils::split(vector<string>& res, const string& s, const string& tok)
{
    int cutAt;
    int Offset = 0;
    res.clear();

    while ((cutAt = s.find_first_of(tok, Offset) - Offset) + Offset != s.npos)
    {
        if (cutAt > 0)
            res.push_back(s.substr(Offset, cutAt));

        //s = s.substr(cutAt + 1);
        Offset += cutAt + 1;

    }

    if (s.length() > Offset)
    {
        res.push_back(s.substr(Offset, cutAt));
    }
}
