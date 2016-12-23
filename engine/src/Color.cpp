#include "Color.h"

namespace engine
{
    //------------------------------------------------------------------
    ColorRGB::ColorRGB(void) : ColorRGB(.0f, .0f, .0f) { }

    ColorRGB::ColorRGB(const float gray) : ColorRGB(gray, gray, gray) { }

    ColorRGB::ColorRGB(const float r, const float g, const float b)
    {
        this->r = r;
        this->g = g;
        this->b = b;
    }

    ColorRGB::ColorRGB(const ColorRGB & copy) : ColorRGB(copy.r, copy.g, copy.b) { }

    Vec3 ColorRGB::rgb(void) const
    {
        return Vec3(r, g, b);
    }
    Vec3 ColorRGB::rbg(void) const
    {
        return Vec3(r, b, g);
    }
    Vec3 ColorRGB::grb(void) const 
    {
        return Vec3(g, r, b);
    }
    Vec3 ColorRGB::gbr(void) const 
    {
        return Vec3(g, b, r);
    }
    Vec3 ColorRGB::brg(void) const 
    {
        return Vec3(b, r, g);
    }
    Vec3 ColorRGB::bgr(void) const 
    {
        return Vec3(b, g, r);
    }


    //------------------------------------------------------------------
    ColorRGBA::ColorRGBA(void) : ColorRGBA(0.0f, 1.0f) { }

    ColorRGBA::ColorRGBA(const float gray, const float a) : ColorRGBA(gray, gray, gray, a) { }

    ColorRGBA::ColorRGBA(const float r, const float g, const float b) : ColorRGBA(r, g, b, 1.0f) { }

    ColorRGBA::ColorRGBA(const float r, const float g, const float b, const float a) : ColorRGB(r, g, b)
    {
        this->a = a;
    }

    ColorRGBA::ColorRGBA(const ColorRGB & copy) : ColorRGBA(copy.r, copy.g, copy.b) { }

    ColorRGBA::ColorRGBA(const ColorRGBA & copy) : ColorRGBA(copy.r, copy.g, copy.b, copy.a) { }

    Vec4 ColorRGBA::rgba(void) const
    {
        return Vec4(r, g, b, a);
    }
    Vec4 ColorRGBA::rbga(void) const
    {
        return Vec4(r, b, g, a);
    }
    Vec4 ColorRGBA::grba(void) const 
    {
        return Vec4(g, r, b, a);
    }
    Vec4 ColorRGBA::gbra(void) const 
    {
        return Vec4(g, b, r, a);
    }
    Vec4 ColorRGBA::brga(void) const 
    {
        return Vec4(b, r, g, a);
    }
    Vec4 ColorRGBA::bgra(void) const 
    {
        return Vec4(b, g, r, a);
    }

}