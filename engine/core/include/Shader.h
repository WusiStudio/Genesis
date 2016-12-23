#pragma once
#ifndef __SHADER_H__
#define __SHADER_H__

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "Object.h"
#include "File.h"

using std::string;
using std::vector;

namespace engine
{
    enum ShaderType{
        vertex = GL_VERTEX_SHADER,
        fragment = GL_FRAGMENT_SHADER
    };

    class Shader : public Object
    {
    public:

        friend class ShaderProgram;
        
        static Shader & Create(const enum ShaderType type);
        static Shader & Create(const string & fileName, const enum ShaderType type);     
        static Shader & Create(const vector<string> & shaderFiles, const enum ShaderType type);

        //编译shader
        const bool compile(void) const;
        
        //获取shaderId
        const unsigned int shaderId(void) const;
        
    protected:

        CREATEFUNC(Shader);

        Shader(void);
        virtual ~Shader(void);
        const bool init(void) override;
        virtual const bool initWithType(const enum ShaderType type);
        // virtual const bool init(const string & fileName, const enum ShaderType type);
        virtual const bool initWithFiles(const vector<string> & shaderFiles, const enum ShaderType type);
        
    private:
        GLuint m_shaderId;

        //ShaderTemplateCode
        static string VertexShaderCode(void);
        static string FragmentShaderCode(void);

        static string m_versionKey, m_globalCodeKey, m_mainCodeKey;
        
        //编译是否成功
        const bool compileIsSuccessful(void) const;
        
    };
}

#endif //__SHADER_H__