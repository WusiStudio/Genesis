#include "File.h"
#include "WSLog.h"

#include <iostream>
#include <cstring>

#if defined(_WIN32) && !defined(APIENTRY) && !defined(__CYGWIN__) && !defined(__SCITECH_SNAP__)
#include <io.h>
#define ACCESS _access
#else
#include <unistd.h>
#define ACCESS access
#endif

namespace engine
{
    namespace tools
    {
        using WsTools::Log;

        string File::ReadAllText(const string & filePath)
        {
            string result;
            ifstream is(filePath);

            if(!is)
            { 
                Log.error("# File::ReadAllText # filePath is not legal");
                return result;
            }
                
            is.seekg (0, is.end);
            int length = is.tellg();
            is.seekg (0, is.beg);
            
            char * temp = new char[length + 1];
            memset(temp, 0, length + 1);
            is.read (temp,length);
            is.close();
            
            result = string(temp);
            delete[] temp;

            return result;
        }

        const bool File::PathIsExists(const string & path)
        {
            if(ACCESS(path.c_str(), 0) != -1) return true;

            return false;
        }

        File & File::Create(const string & filePath)
        {
            File & result = Create();
            bool fileInit = result.initWithFilePath(filePath);

            assert(fileInit);

            //出错了
            if(!fileInit){ result.initializeError(1); }

            return result;
        }

        const bool File::init()
        {
            if(!Object::init()) { return false; }
            this->_filePath = nullptr;
            return true;
        }

        const bool File::initWithFilePath(const string & filePath)
        {
            this->_filePath = new string(filePath);
            return true;
        }

        const bool File::open(const int mode)
        {
            if(!this->_filePath){ return false; }
            
            return true;
        }

        const bool File::open(const string & filePath, const int mode)
        {
            return true; 
        }

        File::File(void)
        {
            _filePath = nullptr;
        }

        File::~File(void)
        {
            if(this->_filePath)
            {
                delete this->_filePath;
                this->_filePath = nullptr;
            }
        }
    }
}
