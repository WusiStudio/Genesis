#pragma once
#ifndef __SHADER_PROGRAM_H__
#define __SHADER_PROGRAM_H__


#include <string>
#include <vector>
#include <map>
#include "Object.h"
#include "Shader.h"
#include "Vec.h"
#include "Matrix.h"

using std::string;
using std::vector;
using std::map;

namespace engine
{
    class ShaderProgram : public Object
    {
    public:
        
        static ShaderProgram & Create(const vector<const Shader *> & shaderList);
        static ShaderProgram & Create(const string & vShaderPath, const string & fShaderPath);
        static ShaderProgram & Create(const vector<string> & vShaderFiles, const vector<string> & fShaderFiles);
        
        //添加shader
        const bool attachShader(const Shader & shader) const;
        //删除shader
        const bool detachShader(const Shader & shader) const;
        
        //链接shader程序
        const bool linkProgram(void) const;

        //启用着色器
        const bool use(void) const;

        //uniform变量
        // const unsigned short uniformSizeOf(const char * unformName) const;
        const bool uniformSet(const char * uniformName, const float & s) const;
        const bool uniformSet(const char * uniformName, const Vec4 & v) const;
        const bool uniformSet(const char * uniformName, const Matrix4 & m) const;

    protected:

        CREATEFUNC(ShaderProgram);

        ShaderProgram(void);
        
        const bool init(void) override;
        virtual const bool initWithShaderList(const vector<const Shader *> & shaderList);
        virtual const bool initWithShaderFile(const string & vShaderPath, const string & fShaderPath);
        virtual const bool initWithShadersFile(const vector<string> & vShaderFiles, const vector<string> & fShaderFiles);

        GLuint getUniformLocation(const char * name) const;
        
    private:

        static map<string, ShaderProgram *> ms_shaderProgramsPool;

        unsigned int m_programId;
        
        //链接是否成功
        const bool linkIsSuccessful(void) const;
        //tools
        static const unsigned short TypeSize(const GLenum type);

    };
}

#endif //__SHADER_PROGRAM_H__