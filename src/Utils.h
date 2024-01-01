#pragma once
#include <vector>
#include <string>
using namespace std;

class Utils
{
public:
    //static void wstring_to_string(const wstring& wstr, string& str);
    //static void string_to_wstring(const string& str, wstring& wstr);
    static bool read_all_file(string& res, const string& filename);
    static void trim(string& str);
    static void split(vector<string>& res, const string& s, const string& tok);
};

