#pragma once 
#ifndef __MATERIA_H__
#define __MATERIA_H__

#include "Object.h"
#include "Color.h"
#include "Textrue2D.h"

namespace engine
{
    enum ChartletType {
        //纯色
        Purity,
        //彩色
        Multicolor,
        //贴图
        Chartlet2D
    };

    class Chartlet : public Object
    {
        PROPERTY_R(ColorRGBA, color);
        PROPERTY_R(unsigned int, colorsCount);
    public:
        CREATEFUNC(Chartlet);
        static const Chartlet & defaultChartlet(void);

        static Chartlet & Create(const ColorRGBA & c);
        static Chartlet & Create(const ColorRGBA * colors, const unsigned int count);
        static Chartlet & Create(Textrue2D & textrue2D);
        static Chartlet & Create(const Image & image);
        static Chartlet & Create(const string & img_path);

        const bool color(const ColorRGBA & c);
        
        const bool colors(const ColorRGBA * colors, const unsigned int count);
        const ColorRGBA * colors(void) const;

        const bool chartlet2D(Textrue2D & textrue2D);
        const Textrue2D * chartlet2D(void) const;

        const ChartletType &  chartletType(void) const;
    protected:
        Chartlet(void);
        virtual ~Chartlet(void);
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
        ChartletType m_chartletType; 

    };
}

#endif //__MATERIA_H__