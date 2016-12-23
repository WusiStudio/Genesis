#pragma once
#ifndef __TOOL_H__
#define __TOOL_H__

#include "Object.h"
#include <string>

using namespace std;

namespace engine
{
    namespace tools
    {
        //计算字符串字符数 
        const unsigned getStringLength(const string & str, const string & coding = "utf-8");
        string wsToS(const wstring & ws);
        wstring sTOWs(const string & s);
    }
}

#endif //__TOOL_H__