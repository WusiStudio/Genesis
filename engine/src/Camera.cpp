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
        return true;
    }

    const bool Camera::composition(const float dp)
    {
        return ((CameraInterface &)((World &)root())).composition(dp);
    }

    const bool Camera::protograph(const Matrix4 & eye_matrix, const Matrix4 & screen_matrix) const
    {
        Size2 viewPortSize(eye_matrix[0][3], eye_matrix[1][3]);

        //观察矩阵
        Vec3 m_up = Matrix4::CreateRotationMatrix(accumulativeRotateOffset().convertToVec3()) * Vec3(.0f, 1.0f, .0f);
        Matrix4 lookAtMatrix = Matrix4::CreateLookAtMatrix(position(), m_target, m_up);

        //透视矩阵
        Vec4 rightTop = lookAtMatrix * Vec4(viewPortSize.width, viewPortSize.height, 100.0f, 1.0f);
        Matrix4 projectionMatrix = Matrix4::CreateOrthogonalMatrix(rightTop[0] - viewPortSize.width, rightTop[0], rightTop[1], rightTop[1] - viewPortSize.height, 100.0f, 2000.0f);
        
        return ((CameraInterface &)((World &)root())).protograph(lookAtMatrix, projectionMatrix * screen_matrix);
    }
}