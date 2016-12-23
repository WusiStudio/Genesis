#include "Tool.h"
#include <clocale>
#include <cstring>

using namespace std;

namespace engine
{
    namespace tools
    {    
        //返回字符串实际长度（单位是一个英文字符）
        const unsigned getStringLength(const string & str, const string & coding){
            unsigned result = 0;
            if(coding == "utf-8")
            {
                //根据utf-8编码规则判断一个字符占几个字节
                for(size_t i = 0; i < str.length();)
                {
                    int length = 0;
                    unsigned short temp = str.at(i) & 0x00FF;
                    while((temp << length & 0x00FF) > 1 << 7)
                    {
                        length ++;
                    }
                    //大于０x80的字符是中文并且占两个英文字符的宽度
                    result += temp < 0x80 ? 1 : 2;
                    length = length < 1 ? 1 : length;
                    i += length;
                }
            }else
            {
                //其他编码类型还没有做
                result = str.length();
            }
            return result;
        }

        //宽字与普通字符转换　　初步测试无效...
        string wsToS(const wstring & ws)
        {
            string curLocale = setlocale(LC_ALL, NULL); // curLocale = "C";

            setlocale(LC_ALL, "chs");

            const wchar_t* _Source = ws.c_str();
            size_t _Dsize = 2 * ws.size() + 1;
            char *_Dest = new char[_Dsize];
            memset(_Dest,0,_Dsize);
            wcstombs(_Dest,_Source,_Dsize);
            string result = _Dest;
            delete []_Dest;

            setlocale(LC_ALL, curLocale.c_str());

            return result;
        }

        wstring sTOWs(const string & s)
        {
            setlocale(LC_ALL, "chs");

            const char* _Source = s.c_str();
            size_t _Dsize = s.size() + 1;\
            wchar_t *_Dest = new wchar_t[_Dsize];
            wmemset(_Dest, 0, _Dsize);
            mbstowcs(_Dest,_Source,_Dsize);
            wstring result = _Dest;
            delete []_Dest;

            setlocale(LC_ALL, "C");

            return result;
        }
    }
}