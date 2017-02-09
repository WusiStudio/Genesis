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

    const bool Materia::init(void)
    {
        if(!Object::init()){ return false; }

        //默认类型与颜色
        m_materiaType = MateriaType::Purity;
        m_color = ColorRGBA(1.0f, 1.0f, 1.0f, 1.0f);
        return true;
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