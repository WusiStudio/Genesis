#include "Font.h"
#include "WSLog.h"
#include "Appaction.h"

namespace engine
{

    //----------------------------------------------------------------------------------
    //                                  * Cache *
    //----------------------------------------------------------------------------------

    FontChartletCache & FontChartletCache::Create(const Uuid & uuid, const int font_size)
    {

        //查询缓存对象
        map<const int, FontChartletCache *> & objectMap = *(ms_objectPool.find(uuid.toString()) == ms_objectPool.end() ? 
            new map<const int, FontChartletCache *>() : ms_objectPool[uuid.toString()]);

        if(objectMap.find(font_size) != objectMap.end())
        {
            return *objectMap[font_size];
        }

        //创建新缓存对象
        FontChartletCache & result = Create();
        objectMap[font_size] = &result;
        result.retain();

        return result;
    }

    const bool FontChartletCache::init(void)
    {
        if(!Object::init()){ return false; }

        return true;
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
            isInit = FT_Init_FreeType(&ms_ft);
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

        // FT_Set_Pixel_Sizes(m_face, 0, 48); 

        return true;
    }
}