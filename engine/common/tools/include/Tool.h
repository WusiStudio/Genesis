#pragma once
#ifndef __TOOL_H__
#define __TOOL_H__

#include "BaseObject.h"
#include <string>
#include <vector>

using std::string;
using std::wstring;
using std::vector;

namespace engine
{
    namespace tools
    {
        //计算字符串长度(中文占两个字符)
        const unsigned getStringLength(const string & str, const string & coding = "utf-8");
        //计算字符串字符数
        const unsigned getStringSize(const string & str, const string & coding = "utf-8");

        vector<unsigned int> unicode(const string & str, const string & coding = "utf-8");
        // string ununicode(vector<unsigned int> & source, const string & coding = "utf-8");

        string wsToS(const wstring & ws);
        wstring sTOWs(const string & s, const string & coding = "utf-8");
    }
}

#endif //__TOOL_H__