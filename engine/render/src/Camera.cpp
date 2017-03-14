#include "Camera.h"

namespace engine
{

    Camera::Camera(void): m_target(.0f)
    {
    }

    const bool Camera::init(void)
    {
        if(!Node::init()){ return false; }

        m_cameraType = CameraType::Projection;
        m_viewPortSize = Size2(1440.0f / 2.0f, 900.0f / 2);
        m_viewNear = .1f;
        m_viewFar = 1800.0f;
        m_up = Vec3(.0f, 1.0f, .0f);

        return true;
    }

    const bool Camera::tick(const float dp)
    {
        if(!Node::tick(dp)){ return false; }
        return true;
    }

    const bool Camera::composition(const float dp)
    {
        return ((CameraInterface &)((World &)root())).composition(dp);
    }

    const bool Camera::protograph(const Matrix4 & eye_matrix, const Matrix4 & screen_matrix) const
    {
        //观察矩阵
        Vec3 up = Matrix4::CreateRotationMatrix(accumulativeRotateOffset().convertToVec3()) * m_up;
        Matrix4 lookAtMatrix = Matrix4::CreateLookAtMatrix(position(), m_target, up);
        
        Matrix4 projectionMatrix;

        if(m_cameraType == CameraType::Orthogonal)
            projectionMatrix = Matrix4::CreateOrthogonalMatrix(-m_viewPortSize.width / 2, m_viewPortSize.width / 2, -m_viewPortSize.height / 2, m_viewPortSize.height / 2, m_viewNear, m_viewFar);
        else if(m_cameraType == CameraType::Projection)
            projectionMatrix = Matrix4::CreateProjectionMatrix(45.0f, m_viewPortSize.width / m_viewPortSize.height, m_viewNear, m_viewFar);

        return ((CameraInterface &)((World &)root())).protograph(lookAtMatrix, projectionMatrix * screen_matrix);
    }
}