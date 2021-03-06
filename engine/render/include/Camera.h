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

    enum CameraType    
    {
        Orthogonal,
        Projection
    };

    class Camera : public Node, protected CameraInterface
    {
        PROPERTY(CameraType, cameraType);
        PROPERTY(Size2, viewPortSize);
        PROPERTY(float, viewNear);
        PROPERTY(float, viewFar);
        PROPERTY(Vec3, target);
        PROPERTY(Vec3, up);

    public:
        CREATEFUNC(Camera);
    protected:
        Camera();
        virtual ~Camera(){}
        virtual const bool init(void) override;

        virtual const bool tick(const float dp) override;

        virtual const bool composition(const float dp) override final;
        virtual const bool protograph(const Matrix4 & eye_matrix, const Matrix4 & screen_matrix) const override final;
    private:
        // float m_near, m_far;
    };

}


#endif //__CAMERA_H__