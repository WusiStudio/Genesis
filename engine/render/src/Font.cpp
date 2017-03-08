#include "Font.h"
#include "WSLog.h"
#include "Appaction.h"
#include <vector>

namespace engine
{

    //----------------------------------------------------------------------------------
    //                                  * CharacterInfo *
    //----------------------------------------------------------------------------------
    CharacterInfo::CharacterInfo(void)
    {
        m_textrue2D = nullptr;
    }

    CharacterInfo::~CharacterInfo(void)
    {
        if(m_textrue2D)
        {
            m_textrue2D->release();
        }
    }

    CharacterInfo & CharacterInfo::Create(const vector<char> & bmp_data, const Size2 & bmp_size, const int font_size, const Vec2 & bearing, const int advance)
    {
        CharacterInfo & result = Create();

        bool CharacterInfoInit = result.initWithBmpData(bmp_data, bmp_size, font_size, bearing, advance);

        assert(CharacterInfoInit);

        if(!CharacterInfoInit) { result.initializeError(1); }

        return result;
    }

    const bool CharacterInfo::init(void)
    {
        if(!Object::init())
        {
            return false;
        }

        return true;
    }

    const bool CharacterInfo::initWithBmpData(const vector<char> & bmp_data, const Size2 & bmp_size, const int font_size, const Vec2 & bearing, const int advance)
    {
        Textrue2D & textrue = Textrue2D::Create(bmp_data, bmp_size);
        if(textrue.fault()){ return false; }
        textrue.retain();

        m_textrue2D = &textrue;
        m_bearing = bearing;
        m_advance = advance;
        m_fontSize = font_size;
        m_size = bmp_size;

        return true;
    }

    //----------------------------------------------------------------------------------
    //                                  * Cache *
    //----------------------------------------------------------------------------------

    map<const string, map<const int, FontChartletCache *> *> FontChartletCache::ms_objectPool;

    FontChartletCache & FontChartletCache::Create(const string & font_name, const int font_size)
    {

        //查询缓存对象
        map<const int, FontChartletCache *> & objectMap = *(ms_objectPool.find(font_name) == ms_objectPool.end() ? 
            new map<const int, FontChartletCache *>() : ms_objectPool[font_name]);

        if(objectMap.find(font_size) != objectMap.end())
        {
            return *objectMap[font_size];
        }

        //创建新缓存对象
        FontChartletCache & result = Create();

        bool FontChartletCacheInit = result.initWithFontInfo(font_name, font_size);

        assert(FontChartletCacheInit);

        if(!FontChartletCacheInit) { result.initializeError(1); }

        objectMap[font_size] = &result;
        result.retain();

        return result;
    }

    CharacterInfo * FontChartletCache::cache(const unsigned int char_code)
    {
        if(m_cachePool.find(char_code) != m_cachePool.end())
        {
            return m_cachePool[char_code];
        }

        return nullptr;
    }

    void FontChartletCache::cache(const unsigned int char_code, CharacterInfo & characterInfo)
    {
        m_cachePool[char_code] = &characterInfo;
    }

    const bool FontChartletCache::init(void)
    {
        if(!Object::init()){ return false; }

        return true;
    }

    const bool FontChartletCache::initWithFontInfo(const string & font_name, const int font_size)
    {
        m_fontName = font_name;
        m_fontSize = font_size;

        return true;
    }

    FontChartletCache::~FontChartletCache()
    {
        for(auto item : m_cachePool)
        {
            item.second->release();
        }
        delete (*ms_objectPool[m_fontName])[m_fontSize];
        (*ms_objectPool[m_fontName]).erase(m_fontSize);
    }


    //----------------------------------------------------------------------------------
    //                                  * Font *
    //----------------------------------------------------------------------------------

    FT_Library Font::ms_ft = nullptr;

    bool Font::InitFreeType(void)
    {
        static bool isInit = false;
        if(!isInit)
        {
            isInit = !FT_Init_FreeType(&ms_ft);
        }

        return isInit;
    }

    Font & Font::Create(const string & file_path)
    {
        Font & result = Create();

        bool fontInit = result.initWithFilePath(file_path);

        assert(fontInit);

        if(!fontInit){ result.initializeError(1); }

        return result;
    }

    Font & Font::defaultFont(void)
    {
        static Font & result = Create("default.ttf");
        return result;
    }

    CharacterInfo & Font::loadCharacterInfo(const unsigned int char_code, const int font_size)
    {
        FontChartletCache & fontChartletCache = FontChartletCache::Create(m_fontName, font_size);
        
        CharacterInfo * findResult = fontChartletCache.cache(char_code);
        if(findResult)
        {
            return *findResult;
        }

        FT_Set_Pixel_Sizes(m_face, 0, font_size);

        if(FT_Load_Char(m_face, char_code, FT_LOAD_RENDER))
        {
            Log.error("Failed to load Glyph By char: {0}", char_code);
        }
        
        vector<char> bitmapData(m_face->glyph->bitmap.buffer, m_face->glyph->bitmap.buffer + m_face->glyph->bitmap.width * m_face->glyph->bitmap.rows);

        findResult = &CharacterInfo::Create(bitmapData, Size2(m_face->glyph->bitmap.width, m_face->glyph->bitmap.rows), font_size, Vec2(m_face->glyph->bitmap_left, m_face->glyph->bitmap_top), m_face->glyph->advance.x / 64);
        if(findResult->fault())
        {
            Log.error("create CharacterInfo By bmpData .. Error");
        }

        findResult->retain();
        fontChartletCache.cache(char_code, *findResult);

        return *findResult;
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
        string checkPath = File::PathIsExists(file_path) ? file_path : "";

        if(checkPath.size() <= 0)
        {
            string temp = Appaction::AppactionPath() + "source/font/" + file_path;
            checkPath = File::PathIsExists(temp) ? temp : "";
        }

        if(checkPath.size() <= 0)
        {
            Log.error("Path: [{0}] Is Not Exists!", file_path);
            return false;
        }

        if(FT_New_Face(ms_ft, checkPath.c_str(), 0, &m_face))
        {
            return false;
        }

        return true;
    }
}