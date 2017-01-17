#pragma once
#ifndef __CUBE_H__
#define __CUBE_H__

#include "Geometry.h"

namespace engine
{
    class Cube : public Geometry
    {
    public:
        static Cube & Create(const Size3 & size);

        PROPERTY(Size3, size);
    protected:
        CREATEFUNC(Cube);

        const bool init(void) override;
        virtual const bool init(const Size3 & size);

        const bool draw(const Matrix4 & eye_matrix, const Matrix4 & screen_matrix) const override;

    private:
    };
}

#endif //__CUBE_H__