#pragma once
#ifndef __COLOR_H__
#define __COLOR_H__

#include "Vec.h"

namespace engine
{
    class ColorRGB : public Vec
    {
    public:
        ColorRGB(void);
        ColorRGB(const float gray);
        ColorRGB(const float r, const float g, const float b);

        ColorRGB(const ColorRGB & copy);

        Vec3 rgb(void) const;
        Vec3 rbg(void) const;
        Vec3 grb(void) const;
        Vec3 gbr(void) const;
        Vec3 brg(void) const;
        Vec3 bgr(void) const;

        friend ostream & operator<<(ostream & _stream, const ColorRGB & param);

        float r, g, b;
    };

    //------------------------------------------------------------------
    class ColorRGBA : public ColorRGB
    {
    public:
        ColorRGBA(void);
        ColorRGBA(const float rgba);
        ColorRGBA(const float gray, const float a);
        ColorRGBA(const float r, const float g, const float b);
        ColorRGBA(const float r, const float g, const float b, const float a);

        ColorRGBA(const ColorRGB & copy);
        ColorRGBA(const ColorRGBA & copy);

        Vec4 rgba(void) const;
        Vec4 rbga(void) const;
        Vec4 grba(void) const;
        Vec4 gbra(void) const;
        Vec4 brga(void) const;
        Vec4 bgra(void) const;

        friend ostream & operator<<(ostream & _stream, const ColorRGBA & param);

        float a;
    };
}

#endif //__COLOR_H__