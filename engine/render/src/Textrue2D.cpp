#include "Textrue2D.h"
#include "Image.h"
#include "WSLog.h"

namespace engine
{
    using WsTools::Log;
    Textrue2D & Textrue2D::Create(const string & file_name)
    {
        Textrue2D & result = Create();

        bool textrue2DInit = result.initWithFineName(file_name);

        assert(textrue2DInit);

        if(!textrue2DInit){ result.initializeError(1); }
        
        return result;
    }

    Textrue2D & Textrue2D::Create(const Image & img)
    {
        Textrue2D & result = Create();

        bool textrue2DInit = result.initWithImage(img);

        assert(textrue2DInit);

        if(!textrue2DInit){ result.initializeError(1); }
        
        return result;
    }

    Textrue2D & Textrue2D::Create(const vector<char> & bmp_data, const Size2 & size)
    {
        Textrue2D & result = Create();

        bool textrue2DInit = result.initWithBmpData(bmp_data, size);

        assert(textrue2DInit);

        if(!textrue2DInit){ result.initializeError(1); }
        
        return result;
    }

    const bool Textrue2D::init(void)
    {
        if(!Object::init()){ return false; }
        m_textrueId = 0;
        return true;
    }

    const bool Textrue2D::initWithFineName(const string & file_name)
    {
        Image & sourceImage = Image::Create(file_name);

        if(!initWithImage(sourceImage)){ return false; }

        return true;
    }

     const bool Textrue2D::initWithImage(const Image & img)
     {

        if(!img.ready()){ return false; }

        //创建纹理
        glGenTextures(1, &m_textrueId);
        //绑定纹理
        glBindTexture(GL_TEXTURE_2D, m_textrueId);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.width(), img.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img.data());
        glGenerateMipmap(GL_TEXTURE_2D);

        //解绑纹理
        glBindTexture(GL_TEXTURE_2D, 0);

        return true;
     }

     const bool Textrue2D::initWithBmpData(const vector<char> & bmp_data, const Size2 & size)
     {
         glPixelStorei(GL_UNPACK_ALIGNMENT, 1); 
        //创建纹理
        glGenTextures(1, &m_textrueId);
        //绑定纹理
        glBindTexture(GL_TEXTURE_2D, m_textrueId);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, size.width, size.height, 0, GL_RED, GL_UNSIGNED_BYTE, reinterpret_cast<const unsigned char*>(&bmp_data[0]));
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        //解绑纹理
        glBindTexture(GL_TEXTURE_2D, 0);

        return true;
     }

     Textrue2D::~Textrue2D()
     {
        if(glIsTexture(m_textrueId) == GL_TRUE)
        {
            glDeleteTextures(1, &m_textrueId);
        }
     }
    
}