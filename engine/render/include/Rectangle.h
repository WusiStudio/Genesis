#pragma once
#ifndef __RECTANGLE_H__
#define __RECTANGLE_H__

#include "Geometry.h"
#include "Vec.h"

namespace engine
{
    class Rectangle : public Geometry
    {
        PROPERTY(Size2, size);
    public:
        static Rectangle & Create(const Size2 & size);
    protected:
        CREATEFUNC(Rectangle);

        virtual const bool init(void) override;
        virtual const bool init(const Size2 & size);

        virtual const bool draw(const Matrix4 & eye_matrix, const Matrix4 & screen_matrix) const override;
    };
}


#endif  //__RECTANGLE_H__