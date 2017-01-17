#include "Matrix.h"
#include <cmath>

namespace engine
{
    //------------------------------------------------------------------
    Matrix2::Matrix2(void) : Matrix()
    {

    }

    Matrix2::Matrix2(const float v) : Matrix2()
    {
        operator[](0)[0] = v;
        operator[](1)[1] = v;
    }

    Matrix2::Matrix2(const Vec2 & v) : Matrix2()
    {
        operator[](0)[0] = v[0];
        operator[](1)[1] = v[1];
    }

    Matrix2::Matrix2(const Vec2 & v_1, const Vec2 & v_2) : Matrix2()
    {
        operator[](0) = v_1;
        operator[](1) = v_2;
    }

    Matrix2::Matrix2(const Matrix2 & copy) : Matrix2(copy[0], copy[1])
    {
    }

    const float Matrix2::det(void) const
    {
        return operator[](0)[0] * operator[](1)[1] - operator[](0)[1] * operator[](1)[0];
    }

    float Matrix2::cofactor(int x, int y) const
    {
        return operator[](x == 0 ? 1 : 0)[y == 0 ? 1 : 0];
    }

    Matrix2 Matrix2::adjugate(void) const
    {
        return Matrix2(Vec2(operator[](1)[1], -operator[](0)[1]), 
        Vec2(-operator[](1)[0], operator[](0)[0]));
    }

    Matrix2 Matrix2::inverse(void) const
    {
        return adjugate() / det();
    }

    //------------------------------------------------------------------
    Matrix3::Matrix3(void) : Matrix()
    {

    }

    Matrix3::Matrix3(const float v) : Matrix3()
    {
        operator[](0)[0] = v;
        operator[](1)[1] = v;
        operator[](2)[2] = v;
    }

    Matrix3::Matrix3(const Vec3 & v) : Matrix3()
    {
        operator[](0)[0] = v[0];
        operator[](1)[1] = v[1];
        operator[](2)[2] = v[2];
    }

    Matrix3::Matrix3(const Vec3 & param1, const Vec3 & param2, const Vec3 & param3) : Matrix3()
    {
        operator[](0) = param1;
        operator[](1) = param2;
        operator[](2) = param3;
    }

    Matrix3::Matrix3(const Matrix3 & copy) : Matrix3(copy[0], copy[1], copy[2])
    {

    }

    //行列式
    const float Matrix3::det(void) const
    {
        const int dimension = 3;
        float result = .0f;
        float computeTempA[dimension], computeTempB[dimension];
        for(int i = 0; i < dimension; ++i)
        {
            for(int j = 0; j < dimension; j++)
            {
                if(!i)
                {
                    computeTempA[j] = 1.0f;
                    computeTempB[j] = 1.0f;
                }

                computeTempA[j] *= operator[](i)[(j + i) % dimension];
                computeTempB[j] *= operator[](i)[(j - i + dimension) % dimension];
            }
        }

        for(int i = 0; i < dimension; ++i)
        {
            result += computeTempA[i] - computeTempB[i];
        }

        return result;
    }

    //余子式
    float Matrix3::cofactor(int x, int y) const
    {
        float computeTemp[2];
        float result;
        for(int i = 0; i < 2; ++i)
        {
            for(int j = 0; j < 2; ++j)
            {
                //初始化数组元素
                if(!i) { computeTemp[j] = 1.0f; }

                //计算位置
                int _x = i;
                int _y = (j + i) % 2;
                _x = _x >= x ? _x + 1 : _x;
                _y = _y >= y ? _y + 1 : _y;

                computeTemp[j] *= operator[](_x)[_y];
            }
        }
        result = computeTemp[0] - computeTemp[1];
        return (x + y) % 2 ? 0 - result : result;
    }

    //伴随矩阵
    Matrix3 Matrix3::adjugate(void) const
    {
        const int dimension = 3;
        Matrix3 result;
        for(int i = 0; i < dimension; ++i)
        {
            for(int j = 0; j < dimension; ++j)
            {
                result.operator[](i)[j] = cofactor(i, j);
            }
        }

        return result;
    }

    //逆阵
    Matrix3 Matrix3::inverse(void) const
    {
        const int dimension = 3;
        Matrix3 result;

        for(int i = 0; i < dimension; ++i)
        {
            for(int j = 0; j < dimension; ++j)
            {
                result.operator[](j)[i] = cofactor(i, j);
            }
        }

        return result / det();
    }

    //------------------------------------------------------------------
    Matrix4::Matrix4(void) : Matrix()
    {

    }

    Matrix4::Matrix4(const float v) : Matrix4(v, v, v, v)
    {

    }

    Matrix4::Matrix4(const Vec4 & v) : Matrix4(v[0], v[1], v[2], v[3])
    {

    }

    Matrix4::Matrix4(const float s1, const float s2, const float s3, const float s4) : Matrix4()
    {
        operator[](0)[0] = s1;
        operator[](1)[1] = s2;
        operator[](2)[2] = s3;
        operator[](3)[3] = s4;
    }

    Matrix4::Matrix4(const Vec4 & v1, const Vec4 & v2, const Vec4 & v3, const Vec4 & v4) : Matrix4()
    {
        operator[](0) = v1;
        operator[](1) = v2;
        operator[](2) = v3;
        operator[](3) = v4;
    }

    Matrix4::Matrix4(const Matrix4 & copy) : Matrix4(copy[0], copy[1], copy[2], copy[3])
    {
        
    }

    Matrix4 Matrix4::CreateTranslationMatrix(const Size3 & size)
    {
        Matrix4 result(1.0f);

        result[0][3] = size.width;
        result[1][3] = size.height;
        result[2][3] = size.depth;

        return result;
    }

    Matrix4 Matrix4::CreateRotationMatrix(const Vec3 & angle)
    {
        Matrix4 rotationX(1.0f), rotationY(1.0f), rotationZ(1.0f);
        float x = angle.x, y = angle.y, z = angle.z;

        //绕x轴旋转
        rotationX[1][1] = cos(x);
        rotationX[1][2] = -sin(x);

        rotationX[2][1] = sin(x);
        rotationX[2][2] = cos(x);


        //绕y轴旋转
        rotationY[0][0] = cos(y);
        rotationY[0][2] = -sin(y);

        rotationY[0][0] = sin(y);
        rotationY[2][2] = cos(y);

        //绕z轴旋转
        rotationY[0][0] = cos(z);
        rotationY[0][1] = -sin(z);

        rotationY[1][0] = sin(z);
        rotationY[1][1] = cos(z);

        return rotationX * rotationY * rotationZ;
    }

    Matrix4 Matrix4::CreateScaleMatrix(const Vec3 & scale)
    {
        Matrix4 result(1.0f);

        result[0][0] = scale.x;
        result[1][1] = scale.y;
        result[2][2] = scale.z;

        return result;
    }

    Matrix4 Matrix4::CreateLookAtMatrix(const Vec3 & position, const Vec3 & target, const Vec3 & world_up)
    {
        Matrix4 result(1.0f);

        Vec3 d = (position - target.convertToSize3()).normalize();
        Vec3 r = world_up.cross(d).normalize();
        Vec3 u = d.cross(r).normalize();

        result[0][3] = 0 - position.x;
        result[1][3] = 0 - position.y;
        result[2][3] = 0 - position.z;

        result[0][0] = r.x;
        result[1][0] = r.y;
        result[2][0] = r.z;

        result[0][1] = u.x;
        result[1][1] = u.y;
        result[2][1] = u.z;

        result[0][2] = d.x;
        result[1][2] = d.y;
        result[2][2] = d.z;

        return result;
    }

    Matrix4 Matrix4::CreateOrthogonalMatrix(const float left, const float right, const float top, const float bottom, const float near, const float far)
    {
        Matrix4 result(1.0f);

        result[0][0] = 2.0f / (right - left);
        result[1][1] = 2.0f / (top - bottom);
        result[2][2] = 0 - 2.0f / (far - near);


        result[0][3] = 0 - (right + left) / (right - left);
        result[1][3] = 0 - (top + bottom) / (top - bottom);
        result[2][3] = 0 - (far + near) / (far - near);

        return result;
    }

    Matrix4 Matrix4::CreateProjectionMatrix(const float left, const float right, const float top, const float bottom, const float near, const float far)
    {
        Matrix4 result(0.0f);

        result[0][0] = near * 2.0f / (right - left);
        result[1][1] = near * 2.0f / (top - bottom);
        result[2][2] = 0 - (far + near) / (far - near);


        // result[0][2] = (right + left) * 2 / (right - left);
        // result[1][2] = (top + bottom) * 2 / (top - bottom);
        result[2][3] = far * near * 2.0f / (far - near);

        result[3][2] = -1.0f;

        Log.info("result: {0}", result);

        return result;
    }

    Matrix4 Matrix4::CreateProjectionMatrix(const Size2 & viewPortSize, const float near, const float far)
    {
        Matrix4 result(0.0f);

        result[0][0] = 2.0f * near / viewPortSize.width;

        result[1][1] = 2.0f * near / viewPortSize.height;

        result[2][2] = 0 - (near + far) / (far - near);
        result[2][3] = 2.0f * near * far / (far - near);

        result[3][2] = -1.0f;

        return result;
    }
}