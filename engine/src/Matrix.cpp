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
        static Matrix4 result(1.0f);

        result[0][3] = size.width;
        result[1][3] = size.height;
        result[2][3] = size.depth;

        return result;
    }

    Matrix4 Matrix4::CreateRotationMatrix(const Vec3 & angle)
    {
        static Matrix4 rotationX(1.0f), rotationY(1.0f), rotationZ(1.0f);
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
        static Matrix4 result(1.0f);

        result[0][0] = scale.x;
        result[1][1] = scale.y;
        result[2][2] = scale.z;

        return result;
    }

    Matrix4 Matrix4::CreateProjectionMatrix(const Size2 & viewPortSize)
    {
        static Matrix4 result(1.0f);

        result[0][0] = 1.0f / viewPortSize.width;
        result[1][1] = 1.0f / viewPortSize.height;

        result[0][3] = -1.0f;
        result[1][3] = -1.0f;

        return result;
    }
}