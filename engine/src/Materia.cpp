#include "Materia.h"

#include <cstring>

using namespace std;

namespace engine
{

    Materia * Materia::ms_defaultMateria = nullptr;

    const Materia & Materia::defaultMateria(void)
    {
        if(!ms_defaultMateria)
        {
            ms_defaultMateria = &Materia::Create();
            ms_defaultMateria->retain();
        }
        return *ms_defaultMateria;
    }

    Materia::Materia(void)
    {
        m_colors = nullptr;
        m_colorsCount = 0;
    }

    Materia::~Materia(void)
    {
        clearData();
    }

    const bool Materia::init(void)
    {
        if(!Object::init()){ return false; }

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

    const ColorRGBA & Materia::color(void) const 
    {
        return m_color;
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

        return true;
    }

    const ColorRGBA * Materia::colors(void) const 
    {
        return m_colors;
    }

    const unsigned int Materia::colorsCount(void) const 
    {
        return m_colorsCount; 
    }

    const MateriaType & Materia::materiaType(void) const 
    {
        return m_materiaType;
    }

    void Materia::clearData(void)
    {
        if(m_colors != nullptr)
        {
            delete[] m_colors;
            m_colors = nullptr;
            m_colorsCount = 0;
        }
    }
}