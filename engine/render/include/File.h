#pragma once
#ifndef __FILE_H__
#define __FILE_H__

#include "Object.h"
#include <string>
#include <fstream>
#include <vector>

using std::ios;
using std::string;
using std::ifstream;
using std::vector;

namespace engine
{

    class File: public Object
    {
    public:

        //判断文件夹或文件是否存在
        static const bool PathIsExists(const string & path);

        //读取整个文件
        static vector<char> ReadAll(const string & file_path);

        //以文本格式读取整个文件
        static string ReadAllText(const string & file_path);

        CREATEFUNC(File);
        static File & Create(const string & file_path);
    
        const bool open(const int mode = ios::in | ios::out);
        const bool open(const string & file_path, const int mode = ios::in | ios::out);
        
    protected:
        virtual const bool init(void) override;
        virtual const bool initWithFilePath(const string & file_path);
        
        File(void);
        virtual ~File(void);
        
    private:
        string * _filePath;
    };
}

#endif //__FILE_H__



