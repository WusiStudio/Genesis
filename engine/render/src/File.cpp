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
    using WsTools::Log;

    const bool File::PathIsExists(const string & path)
    {
        return ACCESS(path.c_str(), 0) != -1;
    }

    vector<char> File::ReadAll(const string & file_path)
    {
        ifstream file(file_path, std::ios::binary);

        if(file.fail())
        { 
            Log.error("# File::ReadAllText # file_path is not legal");
            return vector<char>();
        }

        std::streampos begin, end;
        begin = file.tellg();
        file.seekg( 0, std::ios::end );
        end = file.tellg();
            
        std::vector<char> result( (size_t)(end - begin) );
        file.seekg( 0, std::ios::beg );
        file.read( &result[0], end - begin );
        file.close();

        return result;
    }

    string File::ReadAllText(const string & file_path)
    {
        const vector<char> & binaryContent = ReadAll(file_path);
        return string(binaryContent.begin(), binaryContent.end());
    }

    File & File::Create(const string & file_path)
    {
        File & result = Create();
        bool fileInit = result.initWithFilePath(file_path);

        assert(fileInit);

        //出错了
        if(!fileInit){ result.initializeError(1); }

        return result;
    }

    const Uuid File::uuid(void) const
    {
        ifstream uuid_ifstream(*m_filePath, std::ios::binary);

        MD5 tempMD5(uuid_ifstream);

        return tempMD5.digest();
    }

    const bool File::init()
    {
        if(!Object::init()) { return false; }
        this->m_filePath = nullptr;
        return true;
    }

    const bool File::initWithFilePath(const string & file_path)
    {
        if(!PathIsExists(file_path)){ return false; }
        this->m_filePath = new string(file_path);
        return true;
    }

    const bool File::open(const int mode)
    {
        if(!this->m_filePath){ return false; }

        m_fileIStream = ifstream(*m_filePath, mode);
        if(m_fileIStream.fail())
        {
            return false;
        }
        
        return true;
    }

    File::File(void)
    {
        m_filePath = nullptr;
    }

    File::~File(void)
    {
        if(this->m_filePath)
        {
            delete this->m_filePath;
            this->m_filePath = nullptr;
        }
    }
}
