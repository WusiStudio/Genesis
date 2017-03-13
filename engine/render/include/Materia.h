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
        PROPERTY_R(ColorRGBA, color);
        PROPERTY_R(unsigned int, colorsCount);
    public:
        CREATEFUNC(Materia);
        static const Materia & defaultMateria(void);

        static Materia & Create(const ColorRGBA & c);
        static Materia & Create(const ColorRGBA * colors, const unsigned int count);
        static Materia & Create(Textrue2D & textrue2D);
        static Materia & Create(const Image & image);
        static Materia & Create(const string & img_path);

        const bool color(const ColorRGBA & c);
        
        const bool colors(const ColorRGBA * colors, const unsigned int count);
        const ColorRGBA * colors(void) const;

        const bool chartlet2D(Textrue2D & textrue2D);
        const Textrue2D * chartlet2D(void) const;

        const MateriaType &  materiaType(void) const;
    protected:
        Materia(void);
        virtual ~Materia(void);
        virtual const bool init(void) override;
        virtual const bool initWithColor(const ColorRGBA & c);
        virtual const bool initWithColors(const ColorRGBA * colors, const unsigned int count);
        virtual const bool initWithTextrue2D(Textrue2D & textrue2D);
        virtual const bool initWithImage(const Image & image);
        virtual const bool initWithImagePath(const string & img_path);
    private:
        void clearData(void);

        ColorRGBA * m_colors;
        Textrue2D * m_textrue2D;
        MateriaType m_materiaType; 

    };
}

#endif //__MATERIA_H__