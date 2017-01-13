#pragma once
#ifndef __CIRCLE_H__
#define __CIRCLE_H__

#include "Geometry.h"

namespace engine
{
    class Circle : public Geometry
    {
    public:
        static Circle & Create(const float r);

        const bool radius(const float r);
        const float radius(void);

    protected:

        Circle(void);
        ~Circle(void){}

        CREATEFUNC(Circle);

        const bool init(void) override;
        virtual const bool init(const float r);

        const bool tick(const float dp) override;
        const bool draw(const Matrix4 & eye_matrix, const Matrix4 & screen_matrix) const override;

    private:
        float m_radius;
        float m_density;
    };
}

#endif //__CIRCLE_H__