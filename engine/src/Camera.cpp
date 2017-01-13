#include "Camera.h"

namespace engine
{
    const bool Camera::init(void)
    {
        if(!Node::init()){ return false; }
        
        return true;
    }

    const bool Camera::tick(const float dp)
    {
        if(!Node::tick(dp)){ return false; }
        Vec3 m_up = Matrix4::CreateRotationMatrix(accumulativeRotateOffset().convertToVec3()) * Vec3(.0f, 1.0f, .0f);
        // m_projectionMatrix = 
        return true;
    }

    const bool Camera::composition(const float dp)
    {
        return ((CameraInterface &)((World &)root())).composition(dp);
    }

    const bool Camera::protograph(void) const
    {
        return ((CameraInterface &)((World &)root())).protograph();
    }
}