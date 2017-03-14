#pragma once
#ifndef __FONT_H__
#define __FONT_H__

#include "Object.h"
#include "File.h"
#include <ft2build.h>
#include FT_FREETYPE_H 

#include <map>
#include "Object.h"
#include "Uuid.h"
#include "Image.h"
#include "Textrue2D.h"
#include "Vec.h"

using std::map;

namespace engine
{
    class CharacterInfo : public Object
    {
        PROPERTY_R(Size2, size);
        PROPERTY_R(Vec2, bearing);
        PROPERTY_R(int, advance);
        PROPERTY_R(Textrue2D *, textrue2D);
        PROPERTY_R(int, fontSize);
    public:
        static CharacterInfo & Create(const vector<char> & bmp_data, const Size2 & bmp_size, const int font_size, const Vec2 & bearing, const int advance);
    protected:
        CREATEFUNC(CharacterInfo);
        virtual const bool init(void) override;
        virtual const bool initWithBmpData(const vector<char> & bmp_data, const Size2 & bmp_size, const int font_size, const Vec2 & bearing, const int advance);

        CharacterInfo(void);
        virtual ~CharacterInfo(void);
    private:
    };

    class FontChartletCache : public Object
    {
    public:
        static FontChartletCache & Create(const string & font_name, const int font_size);

        CharacterInfo * cache(const unsigned int);
        void cache(const unsigned int, CharacterInfo & characterInfo);

    protected:
        virtual const bool init(void) override;
        virtual const bool initWithFontInfo(const string & font_name, const int font_size);
        FontChartletCache(void);
        virtual ~FontChartletCache(void);
    private:
        CREATEFUNC(FontChartletCache);
        static map<const string, map<const int, FontChartletCache *> *> ms_objectPool;
        map<const unsigned int, CharacterInfo *> m_cachePool;

        string m_fontName;
        int m_fontSize;
    };

    class Font : public Object
    {
    public:
        static bool InitFreeType(void);
        static Font & Create(const string & file_path);
        static Font & defaultFont(void);

        CharacterInfo & loadCharacterInfo(const unsigned int char_code, const int font_size);
    protected:
        CREATEFUNC(Font);

        virtual const bool init(void) override;
        virtual const bool initWithFilePath(const string & file_path);
        Font(void);
        virtual ~Font(void){}
    private:
        static FT_Library ms_ft;

        string m_fontName;
        FT_Face m_face;
    };
}

#endif //__FONT_H__