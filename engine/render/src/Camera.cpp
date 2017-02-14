#include "Camera.h"

namespace engine
{
    const bool Camera::init(void)
    {
        if(!Node::init()){ return false; }

        m_cameraType = CameraType::Projection;
        m_viewPortSize = Size2(1440.0f / 2.0f, 900.0f / 2);
        m_near = 800.0f;
        m_far = 1800.0f;

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
        Vec3 m_up = Matrix4::CreateRotationMatrix(accumulativeRotateOffset().convertToVec3()) * Vec3(.0f, 1.0f, .0f);
        Matrix4 lookAtMatrix = Matrix4::CreateLookAtMatrix(position(), m_target, m_up);

        // Log.info("lookAtMatrix: {0}", lookAtMatrix);

        //透视矩阵
        Vec4 leftBottom = lookAtMatrix * Vec4(-m_viewPortSize.width / 2.0f, -m_viewPortSize.height / 2.0f, m_near, 1.0f);
        Vec4 rightTop = lookAtMatrix * Vec4(m_viewPortSize.width / 2.0f, m_viewPortSize.height / 2.0f, m_near, 1.0f);
        
        Matrix4 projectionMatrix;

        // Log.info("rightTop: {0}", rightTop);
        
        if(m_cameraType == CameraType::Orthogonal)
            projectionMatrix = Matrix4::CreateOrthogonalMatrix(leftBottom[0], rightTop[0], rightTop[1], leftBottom[1], m_near, m_far);
        else if(m_cameraType == CameraType::Projection)
            projectionMatrix = Matrix4::CreateProjectionMatrix(leftBottom[0], rightTop[0], rightTop[1], leftBottom[1], m_near, m_far);
        
        // Log.info("projectionMatrix: {0}", projectionMatrix);

        return ((CameraInterface &)((World &)root())).protograph(lookAtMatrix, projectionMatrix * screen_matrix);
    }
}