#pragma once
#ifndef __CAMERA_OUTPUT_H__
#define __CAMERA_OUTPUT_H__

#include "Node.h"
#include "CameraInterface.h"
#include "Camera.h"
#include "Matrix.h"


namespace engine
{
    enum CoordinateSystem{
        Screen = 0,
        OpenGL
    };

    class CameraOutput : public Node, protected CameraInterface
    {
        PROPERTY_R(Size2, size);
        PROPERTY(CoordinateSystem, coordinate);
    public:
        CREATEFUNC(CameraOutput);

        Camera & camera(void) const;
        void camera(Camera & linkCamera);

        void size(const Size2 & size);
    protected:
        virtual const bool init(void) override;

        virtual const bool tick(const float dt) override;
        //绘制
        virtual const bool draw(const Matrix4 & eye_matrix, const Matrix4 & screen_matrix) const override;
        
        virtual const bool composition(const float dp) override final;
        virtual const bool protograph(const Matrix4 & eye_matrix, const Matrix4 & screen_matrix) const override final;

        CameraOutput(void);
        virtual ~CameraOutput(void);
    private:
        Camera * m_camera;
    };
}

#endif //__CAMERA_OUTPUT_H__