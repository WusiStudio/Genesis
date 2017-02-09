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
        Camera():m_target(0.0f){}
        virtual ~Camera(){}
        virtual const bool init(void) override;

        virtual const bool tick(const float dp) override;

        virtual const bool composition(const float dp) override final;
        virtual const bool protograph(const Matrix4 & eye_matrix, const Matrix4 & screen_matrix) const override final;
    private:

        Vec3 m_target;
    };
}


#endif //__CAMERA_H__