#include "ShaderProgram.h"
#include "WSLog.h"

namespace engine
{
    using WsTools::Log;

    //着色器缓存池
    map<string, ShaderProgram *> ShaderProgram::ms_shaderProgramsPool;

    ShaderProgram & ShaderProgram::Create(const vector<const Shader *> & shader_list)
    {

        //* 待实现 __着色器缓存池__

        ShaderProgram & result = Create();
        bool shaderProgramInit = result.initWithshader_list(shader_list);

        assert(shaderProgramInit);

        if(!shaderProgramInit){ result.initializeError(1); }
        return result;
    }

    ShaderProgram & ShaderProgram::Create(const string & vShaderPath, const string & f_shader_path)
    {

        //* 待实现 __着色器缓存池__

        ShaderProgram & result = Create();
        bool shaderProgramInit = result.initWithShaderFile(vShaderPath, f_shader_path);

        assert(shaderProgramInit);

        if(!shaderProgramInit){ result.initializeError(1); }
        return result; 
    }

    ShaderProgram & ShaderProgram::Create(const vector<string> & v_shader_files, const vector<string> & f_shader_files)
    {

        //* 待实现 __着色器缓存池__

        ShaderProgram & result = Create();
        bool shaderProgramInit = result.initWithShadersFile(v_shader_files, f_shader_files);

        assert(shaderProgramInit);

        if(!shaderProgramInit){ result.initializeError(1); }
        return result; 
    }

    const bool ShaderProgram::init(void)
    {
        if(!Object::init()){ return false; }

        m_programId = glCreateProgram();
        if(glIsProgram(m_programId) != GL_TRUE){ return false; }

        return true;
    }

    const bool ShaderProgram::initWithshader_list(const vector<const Shader *> & shader_list)
    {
        for(auto item : shader_list)
        {
            if(!item->compileIsSuccessful())
            {
                Log.error("ShaderProgram::init Shader Is Not Compiled!");
                return false;
            }

            if(!attachShader(*item)){ return false; }
        }
        
        return true;
    }

    const bool ShaderProgram::initWithShaderFile(const string & vShaderPath, const string & f_shader_path)
    {
    
        Shader & vertexShader = vShaderPath.size() <= 0 ? Shader::Create(ShaderType::vertex) : Shader::Create(vShaderPath, ShaderType::vertex);
        if(!vertexShader.compile()){ return false; }

        Shader & fragmentShader = f_shader_path.size() <= 0 ? Shader::Create(ShaderType::fragment) : Shader::Create(f_shader_path, ShaderType::fragment);
        if(!fragmentShader.compile()){ return false; }

        attachShader(vertexShader);
        attachShader(fragmentShader);
        linkProgram();

        if(!linkIsSuccessful()){ return false; }
        
        return true;
    }

    const bool ShaderProgram::initWithShadersFile(const vector<string> & v_shader_files, const vector<string> & f_shader_files)
    {
        Shader & vertexShader = v_shader_files.size() <= 0 ? Shader::Create(ShaderType::vertex) : Shader::Create(v_shader_files, ShaderType::vertex);
        if(!vertexShader.compile()){ return false; }

        Shader & fragmentShader = f_shader_files.size() <= 0 ? Shader::Create(ShaderType::fragment) : Shader::Create(f_shader_files, ShaderType::fragment);
        if(!fragmentShader.compile()){ return false; }

        attachShader(vertexShader);
        attachShader(fragmentShader);
        linkProgram();

        if(!linkIsSuccessful()){ return false; }
        return true;
    }

    ShaderProgram::ShaderProgram(void)
    {
        m_programId = 0;
    }


    const bool ShaderProgram::attachShader(const Shader & shader) const
    {
        const unsigned int shaderId = shader.shaderId();
        if(!shaderId)
        {
            Log.error("# ShaderProgram::attachShader #  Shader Is Not legitimate!");
            return false;
        }
        glAttachShader(m_programId, shaderId);
        return true;
    }

    const bool ShaderProgram::detachShader(const Shader & shader) const
    {
        const unsigned int shaderId = shader.shaderId();
        if(!shaderId)
        {
            Log.error("# ShaderProgram::detachShader #  Shader Is Not legitimate!");
            return false;
        }
        glDetachShader(m_programId, shaderId);
        return true;
    }

    const bool ShaderProgram::linkProgram(void) const
    {
        glLinkProgram(m_programId);

        GLint linked;
        glGetProgramiv(m_programId, GL_LINK_STATUS, &linked);
        if(linked == GL_TRUE){ return true; }

        GLint info_len = 0;
        glGetProgramiv(m_programId, GL_INFO_LOG_LENGTH, &info_len);
        if(!info_len){ Log.error("# ShaderProgram::linkProgram #  Not Fined Error Info"); }

        GLchar * buff = new GLchar[info_len];
        glGetProgramInfoLog(m_programId, info_len, nullptr, buff);
        Log.error("# ShaderProgram::linkProgram #  {0}", buff);
        delete [] buff;

        return false;
    }

    const bool ShaderProgram::use(void) const
    {
        if(!linkIsSuccessful()){ return false; }
        glUseProgram(m_programId);
        return true;
    }


    // const unsigned short ShaderProgram::uniformSizeOf(const char * unformName) const
    // {
    //     if(!linkIsSuccessful()){ return false; }
        
    //     GLuint uboIndex = glGetUniformLocation(m_programId, unformName);
    //     if(uboIndex == GL_INVALID_INDEX){
    //         Log.error("unifrom name is invalid");
    //         return 0;
    //     }

    //     GLint uboSize;
    //     GLuint uniformIndices;
    //     glGetActiveUniformsiv((const GLuint )m_programId, uboIndex, &uniformIndices, nullptr, &uboSize);

    //     return (unsigned short)uboSize;
    // }

    const bool ShaderProgram::uniformSet(const char * uniformName, const int d) const
    {
        GLuint uboIndex = getUniformLocation(uniformName);
        if(uboIndex == GL_INVALID_INDEX) return false;

        glUniform1i(uboIndex, d);
        return true;
    }

    const bool ShaderProgram::uniformSet(const char * uniformName, const float & s) const 
    {
        GLuint uboIndex = getUniformLocation(uniformName);
        if(uboIndex == GL_INVALID_INDEX) return false;

        glUniform1f(uboIndex, s);
        return true;
    }
    const bool ShaderProgram::uniformSet(const char * uniformName, const Vec4 & v) const 
    {
        GLuint uboIndex = getUniformLocation(uniformName);
        if(uboIndex == GL_INVALID_INDEX) return false;

        glUniform4fv(uboIndex, 1, &v[0]);
        return true;
    }
    const bool ShaderProgram::uniformSet(const char * uniformName, const Matrix4 & m) const 
    {
        GLuint uboIndex = getUniformLocation(uniformName);
        if(uboIndex == GL_INVALID_INDEX) return false;

        glUniformMatrix4fv(uboIndex, 1, false, &m[0][0]);
        return true;
    }

    GLuint ShaderProgram::getUniformLocation(const char * name) const 
    {
        
        GLuint uboIndex = GL_INVALID_INDEX;

        if(!linkIsSuccessful()){ return uboIndex; }
        
        uboIndex = glGetUniformLocation(m_programId, name);
        if(uboIndex == GL_INVALID_INDEX)
        {
            Log.error("unifrom name is invalid");
            return uboIndex;
        }

        return uboIndex;
    }

    const bool ShaderProgram::linkIsSuccessful(void) const
    {
        if(glIsProgram(m_programId) != GL_TRUE){ return false; }

        GLint linked;
        glGetProgramiv(m_programId, GL_LINK_STATUS, &linked);
        if(linked != GL_TRUE){ return false; }
        
        return true;
    }

    const unsigned short ShaderProgram::TypeSize(const GLenum type)
    {
        unsigned short result;
        #define CASE(Enum, Count, Type) case Enum : result = Count * sizeof(Type); break;

        switch (type) {
            CASE(GL_FLOAT, 1, GLfloat);
            CASE(GL_FLOAT_VEC2, 2, GLfloat);
            CASE(GL_FLOAT_VEC3, 3, GLfloat);
            CASE(GL_FLOAT_VEC4, 4, GLfloat);

            CASE(GL_INT, 1, GLint);
            CASE(GL_INT_VEC2, 2, GLint);
            CASE(GL_INT_VEC3, 3, GLint);
            CASE(GL_INT_VEC4, 4, GLint);

            CASE(GL_UNSIGNED_INT, 1, GLuint);
            CASE(GL_UNSIGNED_INT_VEC2, 2, GLuint);
            CASE(GL_UNSIGNED_INT_VEC3, 3, GLuint);
            CASE(GL_UNSIGNED_INT_VEC4, 4, GLuint);

            CASE(GL_BOOL, 1, GLboolean);
            CASE(GL_BOOL_VEC2, 1, GLboolean);
            CASE(GL_BOOL_VEC3, 1, GLboolean);
            CASE(GL_BOOL_VEC4, 1, GLboolean);

            CASE(GL_FLOAT_MAT2, 4, GLfloat);
            CASE(GL_FLOAT_MAT2x3, 6, GLfloat);
            CASE(GL_FLOAT_MAT2x4, 8, GLfloat);

            CASE(GL_FLOAT_MAT3, 9, GLfloat);
            CASE(GL_FLOAT_MAT3x2, 6, GLfloat);
            CASE(GL_FLOAT_MAT3x4, 12, GLfloat);

            CASE(GL_FLOAT_MAT4, 16, GLfloat);
            CASE(GL_FLOAT_MAT4x2, 8, GLfloat);
            CASE(GL_FLOAT_MAT4x3, 12, GLfloat);

            #undef CASE

        default:
            result = -1;
            break;

        }

        return result;
    }
}