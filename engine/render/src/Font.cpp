#include "Font.h"

namespace engine
{

    FT_Library Font::ms_ft = nullptr;

    bool Font::InitFreeType(void)
    {
        static bool isInit = false;

        if(!isInit)
        {
            isInit = FT_Init_FreeType(&ms_ft);
        }

        return isInit;
    }

    Font & Font::Create(const string & file_path)
    {
        return Create();
    }

    const bool Font::init(void)
    {
        if(!InitFreeType())
        {
            return false;
        }

        return true;
    }

    const bool Font::initWithFilePath(const string & file_path)
    {
        if(FT_New_Face(ms_ft, file_path.c_str(), 0, &m_face))
        {
            return false;
        }

        FT_Set_Pixel_Sizes(m_face, 0, 48); 

        return true;
    }
}