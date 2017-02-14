#pragma once
#ifndef __FONT_H__
#define __FONT_H__

#include "Object.h"
#include "File.h"
#include <ft2build.h>
#include FT_FREETYPE_H  

namespace engine
{
    class Font : public Object
    {
    public:
        static bool InitFreeType(void);
        static Font & Create(const string & file_path);
    protected:
        CREATEFUNC(Font);

        virtual const bool init(void) override;
        virtual const bool initWithFilePath(const string & file_path);
    private:
        Font(){}
        static FT_Library ms_ft;

        FT_Face m_face;
    };

}

#endif //__FONT_H__