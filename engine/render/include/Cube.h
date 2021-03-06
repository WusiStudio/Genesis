#pragma once
#ifndef __CUBE_H__
#define __CUBE_H__

#include "Geometry.h"

namespace engine
{
    class Cube : public Geometry
    {
        PROPERTY(Size3, size);
    public:
        static Cube & Create(const Size3 & size);
    protected:
        CREATEFUNC(Cube);

        virtual const bool init(void) override;
        virtual const bool init(const Size3 & size);

        virtual const bool draw(const Matrix4 & eye_matrix, const Matrix4 & screen_matrix) const override;
        
    };
}

#endif //__CUBE_H__