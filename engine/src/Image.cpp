#include "Image.h"
#include "File.h"
#include "WSLog.h"
#include "Appaction.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace engine
{
    using WsTools::Log;
    
    Image & Image::Create(const string & path)
    {
        Image & result = Create();

        bool imageInit = result.initWithPath(path);

        assert(imageInit);

        if(!imageInit){ result.initializeError(1); }

        return result;
    }

    Image & Image::Create(const vector<char> & binary_data)
    {
        Image & result = Create();

        bool imageInit = result.initWidthBinaryData(binary_data);

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

    const bool Image::initWithPath(const string & path)
    {
        
        string checkPath = File::PathIsExists(path) ? path : "";

        if(checkPath.size() <= 0)
        {
            string temp = Appaction::AppactionPath() + "source/" + path;
            checkPath = File::PathIsExists(temp) ? temp : "";
        }
        
        if(checkPath.size() <= 0)
        {
            Log.error("Path: [{0}] Is Not Exists!", path);
            return false;
        }

        return initWidthBinaryData(File::ReadAll(checkPath));
    }

    const bool Image::initWidthBinaryData(const vector<char> & binary_data)
    {
        if( binary_data.size() == 0 ) 
        {
            return false;
        }

        m_data = stbi_load_from_memory( reinterpret_cast<const unsigned char*>(&binary_data[0]), static_cast<int>(binary_data.size()), &m_width, &m_height, &m_n, 4 );
        if(m_data == nullptr || m_width <= 0 || m_height <= 0 || m_n <= 0)
        {
            Log.error("Could not read image data!");
            return false;
        }

        return true;
    }

    Image::Image(void)
    {
        m_data = nullptr;
    }

    Image::~Image(void)
    {
        if(m_data)
        {
            stbi_image_free( (void *)m_data );
            m_data = nullptr;
        }
    }
}