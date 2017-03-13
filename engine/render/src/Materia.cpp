#include "Materia.h"

#include <cstring>

namespace engine
{
    Materia::Materia(void)
    {
        m_colors = nullptr;
        m_textrue2D = nullptr;
        m_colorsCount = 0;
    }

    Materia::~Materia(void)
    {
        clearData();
    }

    Materia & Materia::Create(const ColorRGBA & c)
    {
        Materia & result = Create();
        bool materiaInitWithColor = result.initWithColor(c);

        assert(materiaInitWithColor);

        if(!materiaInitWithColor){ result.initializeError(1); }

        return result;
    }

    Materia & Materia::Create(const ColorRGBA * colors, const unsigned int count)
    {
        Materia & result = Create();
        bool materiaInitWithColors = result.initWithColors(colors, count);

        assert(materiaInitWithColors);

        if(!materiaInitWithColors){ result.initializeError(1); }

        return result;
    }

    Materia & Materia::Create(Textrue2D & textrue2D)
    {
        Materia & result = Create();
        bool materiaInitWithTextrue2D = result.initWithTextrue2D(textrue2D);

        assert(materiaInitWithTextrue2D);

        if(!materiaInitWithTextrue2D){ result.initializeError(1); }

        return result;
    }

    Materia & Materia::Create(const Image & image)
    {
        Materia & result = Create();
        bool materiaInitWithImage = result.initWithImage(image);

        assert(materiaInitWithImage);

        if(!materiaInitWithImage){ result.initializeError(1); }

        return result;
    }

    Materia & Materia::Create(const string & img_path)
    {
        Materia & result = Create();
        bool materiaInitWithImagePath = result.initWithImagePath(img_path);

        assert(materiaInitWithImagePath);

        if(!materiaInitWithImagePath){ result.initializeError(1); }

        return result;
    }

    const bool Materia::init(void)
    {
        if(!Object::init()){ return false; }

        //默认类型与颜色
        return initWithColor(ColorRGBA(1.0f, 1.0f, 1.0f, 1.0f));
    }

    const bool Materia::initWithColor(const ColorRGBA & c)
    {
        m_materiaType = MateriaType::Purity;
        m_color = c;
        return true;
    }

    const bool Materia::initWithColors(const ColorRGBA * colors, const unsigned int count)
    {
        return this->colors(colors, count);
    }

    const bool Materia::initWithTextrue2D(Textrue2D & textrue2D)
    {
        return chartlet2D(textrue2D);
    }

    const bool Materia::initWithImage(const Image & image)
    {
        Textrue2D & textrue = Textrue2D::Create(image);
        if(textrue.fault()) { return false; }
        return chartlet2D(textrue);
    }

    const bool Materia::initWithImagePath(const string & img_path)
    {
        Image & img = Image::Create(img_path);
        if(img.fault()) { return false; }
        return initWithImage(img);
    }

    const bool Materia::color(const ColorRGBA & c)
    {
        //清除数据
        clearData();

        m_color = c;
        m_materiaType = MateriaType::Purity;
        return true;
    }

    const bool Materia::colors(const ColorRGBA * colors, const unsigned int count)
    {

        if(!colors){ return false; }
        if(!count){ return false; }

        //清除数据
        clearData();

        m_colorsCount = count;

        m_colors = new ColorRGBA[count];
        memcpy(m_colors, colors, sizeof(ColorRGBA) * count);

        m_materiaType = MateriaType::Multicolor;
        return true;
    }

    const ColorRGBA * Materia::colors(void) const 
    {
        return m_colors;
    }

    const bool Materia::chartlet2D(Textrue2D & textrue2D)
    {
        if(!textrue2D.ready())
        {
            return false;
        }

        //清除数据
        clearData();

        m_textrue2D = &textrue2D;
        textrue2D.retain();
        m_materiaType = MateriaType::Chartlet2D;
        return true;
    }
    const Textrue2D * Materia::chartlet2D(void) const
    {
        return m_textrue2D;
    }

    const MateriaType & Materia::materiaType(void) const 
    {
        return m_materiaType;
    }

    void Materia::clearData(void)
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