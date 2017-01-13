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
        m_lookAtMatrix = Matrix4::CreateLookAtMatrix(position(), m_target, m_up);
        m_projectionMatrix = Matrix4::CreateOrthogonalMatrix(Size2(1440.0f / 2.0f, 900.0f / 2), .0f, 2000.0f);
        return true;
    }

    const bool Camera::composition(const float dp)
    {
        return ((CameraInterface &)((World &)root())).composition(dp);
    }

    const bool Camera::protograph(const Matrix4 & eye_matrix, const Matrix4 & screen_matrix) const
    {
        return ((CameraInterface &)((World &)root())).protograph(m_lookAtMatrix * eye_matrix, m_projectionMatrix * screen_matrix);
    }
}