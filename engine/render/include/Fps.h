#pragma once
#ifndef __FPS_H__
#define __FPS_H__

#include "Geometry.h"
#include "Label.h"
#include <vector>

using std::vector;

namespace engine
{
    class Fps: public Geometry
    {
        PROPERTY(Size2, size);
    public:
        CREATEFUNC(Fps);
    protected:

        Fps(void);
        virtual ~Fps(void);
        const bool bindChartlet(Chartlet & c);
        const bool init(void) override;

        virtual const bool tick(const float dp) override;
        virtual const bool draw(const Matrix4 & eye_matrix, const Matrix4 & screen_matrix) const override;
        
    private:
        static int sm_drawFpsCount;
        static float sm_StatisticalInterval;
        Label * m_label;
        int m_dataOffset;

        float m_cacheSumFps;
        int m_cacheFpsCount;
        float m_cacheTime;

        vector<float> m_fpsList;
    };
}

#endif //__FPS_H__