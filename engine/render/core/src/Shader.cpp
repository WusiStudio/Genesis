#include "Shader.h"
#include "WSLog.h"
#include "File.h"
#include "Appaction.h"
#include <cassert>
#include <regex>

namespace engine
{
    using WsTools::Log;

    using std::smatch;
    using std::regex;
    using std::stringstream;
    using std::sregex_iterator;

    string Shader::m_versionKey = "#version";
    string Shader::m_globalCodeKey = "#globalCode";
    string Shader::m_mainCodeKey = "#mainCode";

    Shader & Shader::Create(const enum ShaderType type)
    {
        Shader & result = Create();
        bool shaderInit = result.initWithType(type);

        assert(shaderInit);

        if(!shaderInit){ result.initializeError(1); }
        return result;
    }

    Shader & Shader::Create(const string & file_name, const enum ShaderType type)
    {
        vector<string> fileList(1, file_name);
        return Create(fileList, type);
    }

    Shader & Shader::Create(const vector<string> & shader_files, const enum ShaderType type)
    {
        Shader & result = Create();
        bool shaderInit = result.initWithFiles(shader_files, type);

        assert(shaderInit);

        if(!shaderInit){ result.initializeError(1); }
        return result;
    }

    const bool Shader::init(void)
    {
        if(!Object::init()){ return false; }
        m_shaderId = 0;
        return true;
    }

    const bool Shader::initWithType(const enum ShaderType type)
    {

        string source;
        m_shaderId = glCreateShader(type);
        if(glIsShader(m_shaderId) != GL_TRUE){ return false; }

        switch(type)
        {
        case ShaderType::vertex:
            source = VertexShaderCode();
            break;
        case ShaderType::fragment:
            source = FragmentShaderCode();
            break;
        default:
            Log.error("Unknown Shader Type");
            return false;
        }

        source.replace(source.find(m_globalCodeKey), m_globalCodeKey.size(), "");
        source.replace(source.find(m_mainCodeKey), m_mainCodeKey.size(), "");

        const GLchar * p_source = source.c_str();
        glShaderSource(m_shaderId, 1, &p_source, nullptr);

        return true;
    }

    const bool Shader::initWithFiles(const vector<string> & shader_files, const enum ShaderType type)
    {

        //获取每个文件的路径
        vector<string> filePathList;
        for(auto file_name : shader_files)
        {
            string shaderFilePath = File::PathIsExists(file_name) ? file_name : "";

            if(shaderFilePath.size() <= 0)
            {
                string tempPath = Appaction::AppactionPath() + "shader/" + file_name;
                shaderFilePath = File::PathIsExists(tempPath) ? tempPath : "";
            }

            if(shaderFilePath.size() <= 0)
            {
                Log.error("Shader: [{0}] Is Not Exists!", file_name);
                return false;
            }  
            filePathList.push_back(shaderFilePath);
        }

        //获取代码模板
        string source;
        m_shaderId = glCreateShader(type);
        if(glIsShader(m_shaderId) != GL_TRUE)
        {
            return false;
        }

        switch(type)
        {
        case ShaderType::vertex:
            source = VertexShaderCode();
            break;
        case ShaderType::fragment:
            source = FragmentShaderCode();
            break;
        default:
            Log.error("Unknown Shader Type");
            return false;
        }


        //代码融合
        int version = 330;
        string mainCode = "";
        string globalCode = "";


        for(auto shaderFilePath : filePathList)
        {                
            string code = File::ReadAllText(shaderFilePath);
            string removeAfterCode = code;

            //获取glsl版本
            static regex versionRegex("#version ([\\d]+) core");
            auto matchBegin = sregex_iterator(code.begin(), code.end(), versionRegex);
            auto matchEnd = sregex_iterator();
            int tempVersion = version;
            for(auto item  = matchBegin; item != matchEnd; ++item)
            {
                int temp = atoi(item->str(1).c_str());
                if(temp <= tempVersion){ continue; }
                tempVersion = temp;
            }

            version = tempVersion;

            //  删除注释
            static regex searchAnnotationRegex("#[^\n]*\n|//[^\n]*\n|/\\*[\\s\\S]*?\\*/");
            matchBegin = sregex_iterator(code.begin(), code.end(), searchAnnotationRegex);
            
            for(auto item = matchBegin; item != matchEnd; ++item)
            {
                removeAfterCode.erase(removeAfterCode.find(item->str()), item->str().size());
            }
            
            //拆分代码块
            static regex mainRegex("void\\s+main\\s*\\(\\s*\\)\\s*\\{");
            smatch searchResult;
            if(regex_search(removeAfterCode, searchResult, mainRegex))
            {
                int openLeftBraceCount = 1;
                auto bodyIndex = removeAfterCode.find(searchResult[0].str());
                auto contentIndex = bodyIndex + searchResult[0].str().size();
                auto begin = removeAfterCode.begin();
                auto i = begin + contentIndex;
                for(; i != removeAfterCode.end() && openLeftBraceCount; ++i)
                {
                    if(*i == '{'){ ++openLeftBraceCount; }
                    if(*i == '}'){ --openLeftBraceCount; }
                }
                mainCode += removeAfterCode.substr(contentIndex, i - begin - contentIndex - 1);
                globalCode += removeAfterCode.erase(bodyIndex, i - begin - bodyIndex);
            }
        }

        stringstream sversionCode;
        sversionCode << "#version " << version << " core";

        //替换占位符
        source.replace(source.find(m_versionKey), m_versionKey.size(), sversionCode.str());
        source.replace(source.find(m_globalCodeKey), m_globalCodeKey.size(), globalCode);
        source.replace(source.find(m_mainCodeKey), m_mainCodeKey.size(), mainCode);

        // Log.info("source code: {0}", source);
            
        const GLchar * p_source = source.c_str();
        glShaderSource(m_shaderId, 1, &p_source, nullptr);

        return true;
    }

    Shader::Shader(void)
    {
        m_shaderId = 0;
    }

    const bool Shader::compile(void) const
    {
        glCompileShader(m_shaderId);

        GLint compiled = 0;
        glGetShaderiv(m_shaderId, GL_COMPILE_STATUS, &compiled);
        if(compiled == GL_TRUE){ return true; }

        GLint infoLen = 0;
        glGetShaderiv(m_shaderId, GL_INFO_LOG_LENGTH, &infoLen);

        if(infoLen == 0)
        {
            Log.error("# Shader::compile #  Not Fined Error Info");
            return false;
        }

        GLchar * buff = new GLchar[infoLen];
        glGetShaderInfoLog(m_shaderId, infoLen, nullptr, buff);

        Log.error("# Shader::compile #  {0}", buff);
        delete [] buff;

        return false;
    }

    const unsigned int Shader::shaderId(void) const
    {
        if(!compileIsSuccessful()){ return 0; }

        return m_shaderId;
    }

    const bool Shader::compileIsSuccessful(void) const
    {
        if(glIsShader(m_shaderId) != GL_TRUE){ return false; }

        GLint compiled = 0;
        glGetShaderiv(m_shaderId, GL_COMPILE_STATUS, &compiled);
        return compiled == GL_TRUE;
    }

    Shader::~Shader(void)
    {
        if(glIsShader(m_shaderId) == GL_TRUE)
        {
            glDeleteShader(m_shaderId);
        }
    }

    string Shader::VertexShaderCode(void)
    {
        static string result = File::ReadAllText(Appaction::AppactionPath() + "shader/template.vert");
        return result;
    }

    string Shader::FragmentShaderCode(void)
    {
        static string result = File::ReadAllText(Appaction::AppactionPath() + "shader/template.frag");
        return result;
    }
}