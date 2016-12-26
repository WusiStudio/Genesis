#include "Image.h"
#include "File.h"
#include "WSLog.h"
#include "Appaction.h"
#include "wsimg.h"

namespace engine
{
    using WsTools::Log;
    using tools::File;
    
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

        struct wsimg_info img_info;
        m_data = wsimg_read_data(checkPath.c_str(), &img_info);
        if(!m_data) { return false; }

        m_width = img_info.width;
        m_height = img_info.height;

        return true;
    }

    const int Image::width(void) const
    {
        return m_width;
    }
    const int Image::height(void) const 
    {
        return m_height;
    }
    const unsigned char * Image::data(void) const 
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
            wsimg_free(m_data);
            m_data = nullptr;
        }
    }
}