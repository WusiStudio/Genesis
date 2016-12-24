#pragma once
#ifndef __CAMERA_OUTPUT_H__
#define __CAMERA_OUTPUT_H__

#include "Node.h"
#include "Camera.h"
#include "Matrix.h"

namespace engine
{
    class CameraOutput : public Node
    {
    public:
        CREATEFUNC(CameraOutput);

        Camera & camera(void) const;
        void camera(Camera & linkCamera);

        void size(const Size2 & size);
        const Size2 & size(void) const;

    protected:

        const bool init(void) override;

        const bool tick(const float dt) override;
        //绘制
        const bool draw(const Matrix4 & projection) const override;

        CameraOutput(void);
        virtual ~CameraOutput(void);
    private:
        Camera * m_camera;
        Size2 m_size;
    };
}

#endif //__CAMERA_OUTPUT_H__