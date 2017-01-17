#pragma once 
#ifndef __MATERIA_H__
#define __MATERIA_H__

#include "Object.h"
#include "Color.h"
#include "Textrue2D.h"

namespace engine
{
    enum MateriaType {
        //纯色
        Purity,
        //彩色
        Multicolor,
        //贴图
        Chartlet2D
    };

    class Materia : public Object
    {
    public:
        CREATEFUNC(Materia);
        static const Materia & defaultMateria(void);

        static const Materia & Create(const ColorRGBA & c);
        static const Materia & Create(const ColorRGBA * colors, const unsigned int count);

        const bool color(const ColorRGBA & c);
        
        const bool colors(const ColorRGBA * colors, const unsigned int count);
        const ColorRGBA * colors(void) const;

        const bool chartlet2D(Textrue2D & textrue2D);
        const Textrue2D * chartlet2D(void) const;

        const MateriaType &  materiaType(void) const;

        //
        PROPERTY_R(ColorRGBA, color);
        PROPERTY_R(unsigned int, colorsCount);
    protected:
        Materia(void);
        virtual ~Materia(void);
        const bool init(void) override;
    private:
        void clearData(void);

        ColorRGBA * m_colors;
        Textrue2D * m_textrue2D;
        MateriaType m_materiaType; 

    };
}

#endif //__MATERIA_H__