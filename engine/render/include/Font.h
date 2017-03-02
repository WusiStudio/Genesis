#pragma once
#ifndef __FONT_H__
#define __FONT_H__

#include "Object.h"
#include "File.h"
#include <ft2build.h>
#include FT_FREETYPE_H 

#include <map>
#include "Uuid.h"
#include "Textrue2D.h"

using std::map;

namespace engine
{
    class FontChartletCache : public Object
    {
    public:
        static FontChartletCache & Create(const Uuid & uuid, const int font_size);
    protected:
        virtual const bool init(void) override;
        virtual ~FontChartletCache();
    private:
        CREATEFUNC(FontChartletCache);
        static map<const string, map<const int, FontChartletCache *> *> ms_objectPool;
        map<const unsigned int, Textrue2D *> m_cachePool;
    };

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