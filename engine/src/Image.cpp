#include "Image.h"
// #define STB_IMAGE_IMPLEMENTATION
// #include "std_image.h"
#include "File.h"
#include "WSLog.h"
#include "Appaction.h"

using namespace WsTools;

namespace engine
{
    using namespace tools;
    Image & Image::Create(const string & path)
    {
        Image & result = Create();

        bool imageInit = result.init(path);

        assert(imageInit);

        if(!imageInit){ result.initializeError(1); }

        return result;
    }

    const bool Image::init(void)
    {
        if(!Object::init()){ return false; }
        
        m_width = m_height = m_n = 0;
        m_data = nullptr;

        return true;
    }

    const bool Image::init(const string & path)
    {
        
        string checkPath = File::PathIsExists(path) ? path : "";

        if(checkPath.size() <= 0)
        {
            string temp = Appaction::AppactionPath() + "Source/" + path;
            checkPath = File::PathIsExists(temp) ? temp : "";
        }
        
        if(checkPath.size() <= 0)
        {
            Log.error("Path: [{0}] Is Not Exists!", path);
            return false;
        }

        //  m_data = stbi_load(checkPath.c_str(), &m_width, &m_height, &m_n, 0);

        return true;
    }

    const int Image::width(void) const
    {
        if(!ready()) return 0;

        return m_width;
    }
    const int Image::height(void) const 
    {
        if(!ready()) return 0;

        return m_height;
    }
    unsigned char * Image::data(void) const 
    {
        if(!ready()) return nullptr;

        return m_data;
    }

    Image::Image(void)
    {
        m_data = nullptr;
    }

    Image::~Image(void)
    {
        if(m_data)
        {
            //stbi_image_free(m_data);
            m_data = nullptr;
        }
    }
}