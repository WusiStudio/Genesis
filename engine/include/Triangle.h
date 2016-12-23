#pragma once
#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__
#include "Geometry.h"
#include "Vec.h"

namespace engine
{
    class Triangle: public Geometry
    {
    public:
        static Triangle & Create(const Vec3 & vertex_1, const Vec3 & vertex_2, const Vec3 & vertex_3);
    protected:
        CREATEFUNC(Triangle);
        const bool init(void) override;
        virtual const bool init(const Vec3 & vertex_1, const Vec3 & vertex_2, const Vec3 & vertex_3);

        const bool tick(const float dp) override;
        const bool draw(const Matrix4 & projection) override;
        
        ~Triangle(void){}
    private:

    };
}

#endif //__TRIANGLE_H__