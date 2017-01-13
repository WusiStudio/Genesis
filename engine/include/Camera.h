#pragma once
#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "Node.h"
#include "Vec.h"
#include "Matrix.h"
#include "CameraInterface.h"
#include "World.h"

namespace engine
{
    class Camera : public Node, protected CameraInterface
    {
    public:
        CREATEFUNC(Camera);
    protected:
        Camera(){}
        virtual ~Camera(){}
        const bool init(void) override;

        const bool tick(const float dp) override;

        const bool composition(const float dp) override final;
        const bool protograph(const Matrix4 & eye_matrix, const Matrix4 & screen_matrix) const override final;
    private:

        Vec3 m_target;
        Matrix4 m_lookAtMatrix;
        Matrix4 m_projectionMatrix;
    };
}


#endif //__CAMERA_H__