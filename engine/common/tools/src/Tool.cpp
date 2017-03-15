#include "Tool.h"
#include <locale>
#include "WSLog.h"

using WsTools::Log;

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

        const unsigned getStringSize(const string & str, const string & coding){
            unsigned result = 0;
            if(coding == "utf-8")
            {
                for(size_t i = 0; i < str.length();)
                {
                    size_t byte = 0;
                    unsigned char temp = str.at(i);
                    unsigned char offset = 1 << 7;
                    while(temp & offset)
                    {
                        ++byte;
                        offset = offset >> 1;
                    }

                    i += byte == 0 ? 1 : byte;
                    ++result;
                }
            }else
            {
                //其他编码类型还没有做
                result = str.length();
            }
            return result;
        }

        vector<unsigned int> unicode(const string & str, const string & coding)
        {
            vector<unsigned int> result;
            if(coding == "utf-8")
            {
                for(size_t i = 0; i < str.length();)
                {
                    unsigned int sCode = 0;
                    size_t byte = 0;
                    unsigned char temp = str.at(i);
                    unsigned char offset = 1 << 7;

                    while(temp & offset)
                    {
                        ++byte;
                        offset = offset >> 1;
                    }

                    if(!byte) byte = 1;

                    for(size_t n = 0; n < byte; ++n)
                    {
                        if(n) sCode = sCode << 8;
                        temp = str.at(i + n);
                        for(int j = 1; j < 8; ++j)
                        {
                            offset = 1 << (8 - j);
                            if((temp ^ offset) & offset)
                            {
                                sCode = (sCode | (temp << j & 0x00FF)) >> j;
                                break;
                            }
                        }
                    }
                    result.push_back(sCode);
                    i += byte;
                }
            }

            return result;
        }

        //宽字与普通字符转换
        string wsToS(const wstring & ws)
        {

            //系统转码不可靠 得改
            std::locale old_loc = std::locale::global(std::locale(LOCAL));   
 
            const wchar_t* src_wstr = ws.c_str();   
        
            size_t buffer_size = ws.size() * 4 + 1;   
        
            char* dst_str = new char[buffer_size];   
        
            memset(dst_str, 0, buffer_size);   
        
            wcstombs(dst_str ,src_wstr, buffer_size);   
        
            std::string result = dst_str;   
        
            delete []dst_str;   
        
            std::locale::global(old_loc);   
        
            return result;  
        }

        wstring sTOWs(const string & s, const string & coding)
        {
            //对 unicode 函数支持编码格式有效
            vector<unsigned int> unicodeSource = unicode(s, coding);
            const size_t buffer_size = unicodeSource.size() + 1;  
            wchar_t * dst_wstr = new wchar_t[buffer_size];
            wmemset(dst_wstr, 0, buffer_size);
            for(size_t i = 0; i < buffer_size - 1; ++i)
            {
                dst_wstr[i] = (wchar_t)unicodeSource[i];
            }

            std::wstring result = dst_wstr;  
            delete[] dst_wstr;
            return result;
        }
    }
}