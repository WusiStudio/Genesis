#pragma once
#ifndef __CIRCLE_H__
#define __CIRCLE_H__

#include "Geometry.h"

namespace engine
{
    class Circle : public Geometry
    {
        PROPERTY_R(float, radius);
    public:
        static Circle & Create(const float r);

        const bool radius(const float r);
    protected:

        Circle(void);
        ~Circle(void){}

        CREATEFUNC(Circle);

        virtual const bool init(void) override;
        virtual const bool init(const float r);

        virtual const bool tick(const float dp) override;
        virtual const bool draw(const Matrix4 & eye_matrix, const Matrix4 & screen_matrix) const override;

    private:
        float m_density;
    };
}

#endif //__CIRCLE_H__