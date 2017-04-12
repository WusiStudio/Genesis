#pragma once
#ifndef __FILE_H__
#define __FILE_H__

#include "Object.h"
#include "Uuid.h"
#include "MD5.h"
#include <string>
#include <fstream>
#include <vector>

using std::ios;
using std::string;
using std::ifstream;
using std::vector;

namespace engine
{
    using tools::Uuid;
    using tools::MD5;
    class File: public Object
    {
    public:

        //判断文件夹或文件是否存在
        static const bool PathIsExists(const string & path);

        //读取整个文件
        static vector<char> ReadAll(const string & file_path);

        //以文本格式读取整个文件
        static string ReadAllText(const string & file_path);

        static File & Create(const string & file_path);

        const Uuid uuid(void) const;
    
        const bool open(const std::ios_base::openmode mode = ios::in | ios::out);
        
    protected:
        CREATEFUNC(File);
        virtual const bool init(void) override;
        virtual const bool initWithFilePath(const string & file_path);
        
        File(void);
        virtual ~File(void);
        
    private:
        string * m_filePath;
        ifstream m_fileIStream;
    };
}

#endif //__FILE_H__



