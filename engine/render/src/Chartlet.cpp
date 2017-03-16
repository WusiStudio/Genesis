#include "Chartlet.h"

#include <cstring>

namespace engine
{
    Chartlet::Chartlet(void)
    {
        m_colors = nullptr;
        m_textrue2D = nullptr;
        m_colorsCount = 0;
    }

    Chartlet::~Chartlet(void)
    {
        clearData();
    }

    Chartlet & Chartlet::Create(const ColorRGBA & c)
    {
        Chartlet & result = Create();
        bool chartletInitWithColor = result.initWithColor(c);

        assert(chartletInitWithColor);

        if(!chartletInitWithColor){ result.initializeError(1); }

        return result;
    }

    Chartlet & Chartlet::Create(const ColorRGBA * colors, const unsigned int count)
    {
        Chartlet & result = Create();
        bool chartletInitWithColors = result.initWithColors(colors, count);

        assert(chartletInitWithColors);

        if(!chartletInitWithColors){ result.initializeError(1); }

        return result;
    }

    Chartlet & Chartlet::Create(Textrue2D & textrue2D)
    {
        Chartlet & result = Create();
        bool chartletInitWithTextrue2D = result.initWithTextrue2D(textrue2D);

        assert(chartletInitWithTextrue2D);

        if(!chartletInitWithTextrue2D){ result.initializeError(1); }

        return result;
    }

    Chartlet & Chartlet::Create(const Image & image)
    {
        Chartlet & result = Create();
        bool chartletInitWithImage = result.initWithImage(image);

        assert(chartletInitWithImage);

        if(!chartletInitWithImage){ result.initializeError(1); }

        return result;
    }

    Chartlet & Chartlet::Create(const string & img_path)
    {
        Chartlet & result = Create();
        bool chartletInitWithImagePath = result.initWithImagePath(img_path);

        assert(chartletInitWithImagePath);

        if(!chartletInitWithImagePath){ result.initializeError(1); }

        return result;
    }

    const bool Chartlet::init(void)
    {
        if(!Object::init()){ return false; }

        //默认类型与颜色
        return initWithColor(ColorRGBA(1.0f, 1.0f, 1.0f, 1.0f));
    }

    const bool Chartlet::initWithColor(const ColorRGBA & c)
    {
        m_chartletType = ChartletType::Purity;
        m_color = c;
        return true;
    }

    const bool Chartlet::initWithColors(const ColorRGBA * colors, const unsigned int count)
    {
        return this->colors(colors, count);
    }

    const bool Chartlet::initWithTextrue2D(Textrue2D & textrue2D)
    {
        return chartlet2D(textrue2D);
    }

    const bool Chartlet::initWithImage(const Image & image)
    {
        Textrue2D & textrue = Textrue2D::Create(image);
        if(textrue.fault()) { return false; }
        return chartlet2D(textrue);
    }

    const bool Chartlet::initWithImagePath(const string & img_path)
    {
        Image & img = Image::Create(img_path);
        if(img.fault()) { return false; }
        return initWithImage(img);
    }

    const bool Chartlet::color(const ColorRGBA & c)
    {
        //清除数据
        clearData();

        m_color = c;
        m_chartletType = ChartletType::Purity;
        return true;
    }

    const bool Chartlet::colors(const ColorRGBA * colors, const unsigned int count)
    {

        if(!colors){ return false; }
        if(!count){ return false; }

        //清除数据
        clearData();

        m_colorsCount = count;

        m_colors = new ColorRGBA[count];
        memcpy(m_colors, colors, sizeof(ColorRGBA) * count);

        m_chartletType = ChartletType::Multicolor;
        return true;
    }

    const ColorRGBA * Chartlet::colors(void) const 
    {
        return m_colors;
    }

    const bool Chartlet::chartlet2D(Textrue2D & textrue2D)
    {
        if(!textrue2D.ready())
        {
            return false;
        }

        //清除数据
        clearData();

        m_textrue2D = &textrue2D;
        textrue2D.retain();
        m_chartletType = ChartletType::Chartlet2D;
        return true;
    }
    const Textrue2D * Chartlet::chartlet2D(void) const
    {
        return m_textrue2D;
    }

    const ChartletType & Chartlet::chartletType(void) const 
    {
        return m_chartletType;
    }

    void Chartlet::clearData(void)
    {
        if(m_colors)
        {
            delete[] m_colors;
            m_colors = nullptr;
            m_colorsCount = 0;
        }

        if(m_textrue2D)
        {
            m_textrue2D->release();
        }
    }
}