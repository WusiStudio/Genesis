#pragma once
#ifndef __CAMERA_OUTPUT_H__
#define __CAMERA_OUTPUT_H__

#include "Node.h"
#include "CameraInterface.h"
#include "Camera.h"
#include "Matrix.h"


namespace engine
{
    class CameraOutput : public Node, protected CameraInterface
    {
    public:
        CREATEFUNC(CameraOutput);

        Camera & camera(void) const;
        void camera(Camera & linkCamera);

        PROPERTY(Size2, size);
    protected:

        const bool init(void) override;

        const bool tick(const float dt) override;
        //绘制
        const bool draw(const Matrix4 & eye_matrix, const Matrix4 & screen_matrix) const override;
        
        const bool composition(const float dp) override final;
        const bool protograph(const Matrix4 & eye_matrix, const Matrix4 & screen_matrix) const override final;

        CameraOutput(void);
        virtual ~CameraOutput(void);
    private:
        Camera * m_camera;
    };
}

#endif //__CAMERA_OUTPUT_H__