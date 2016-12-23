#pragma once
#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "Node.h"
#include "Vec.h"
#include "Matrix.h"

namespace engine
{
    class Camera : public Node
    {
    public:
        CREATEFUNC(Camera);
    protected:
        Camera(){}
        const bool init(void) override;

        virtual ~Camera(){}
    private:

        Vec3 m_target, m_up;
        Matrix4 m_projectionMatrix;
    };
}


#endif //__CAMERA_H__