#pragma once
#ifndef __MATRIX_H__
#define __MATRIX_H__

#include "Struct.h"
#include "Vec.h"
#include "WSLog.h"
#include <iostream>

namespace engine
{
    using std::iostream;
    using WsTools::Log;

    template<typename C, typename T, unsigned dimension>
    class Matrix : public Struct
    {
    public:
        T & operator[](const unsigned int index) const
        {
            return *(T *)(&data[index]);
        }

        //取反
        C operator-(void) const
        {
            C result;
            for(unsigned i = 0; i < dimension; ++i)
            {
                result[i] = -operator[](i);
            }
            return result;
        }


        //加法
        C operator+(const C & m) const
        {
            C result;
            for(unsigned i = 0; i < dimension; ++i)
            {
                result[i] = operator[](i) + m[i];
            }
            return result;
        }

        C & operator+=(const C & m)
        {
            for(unsigned i = 0; i < dimension; ++i)
            {
                operator[](i) += m[i];
            }
            return *this;
        }

        //减法
        C operator-(const C & m) const
        {
            return operator+(-m);
        }

        C & operator-=(const C & m)
        {
            return operator+=(-m);
        }

        //乘法
        C operator*(const float & s) const
        {
            C result(.0f);
            for(unsigned int i = 0; i < dimension; ++i)
            {
                for(unsigned int n = 0; n < dimension; ++n)
                {
                    result.operator[](i)[n] = operator[](i)[n] * s;
                }
            }
            return result;
        }


        T operator*(const T & v) const
        {
            T result(.0f);
            for(unsigned int i = 0; i < dimension; ++i)
            {
                for(unsigned int n = 0; n < dimension; ++n)
                {
                    result[i] += v[n] * operator[](i)[n];
                }
            }
            return result;
        }


        C operator*(const C & m) const
        {
            C result;
            for(unsigned int i = 0; i < dimension; ++i)
            {
                for(unsigned int n = 0; n < dimension; ++n)
                {
                    for(unsigned int j = 0; j < dimension; ++j)
                    {
                        result[i][n] += operator[](i)[j] * m[j][n];
                    }
                }
            }
            return result;
        }

        //除法
        C operator/(const float s) const
        {
            C result(.0f);
            for(unsigned int i = 0; i < dimension; ++i)
            {
                for(unsigned int n = 0; n < dimension; ++n)
                {
                    result.operator[](i)[n] = operator[](i)[n] / s;
                }
            }
            return result;
        }


        friend ostream & operator<<(ostream & _stream, const Matrix & m)
        {
            _stream << "Matrix" << dimension << ":" << endl;
            for(unsigned int i = 0; i < dimension; ++i)
            {
                _stream << "\t\t";
                i ? _stream << "  " : _stream << "[ ";
                for(unsigned int n = 0; n < dimension; ++n)
                {
                    if(n) _stream << ", ";
                    _stream << m[i][n];
                }
                i >= dimension - 1 ? _stream << " ]" : _stream << endl;
            }
            return _stream;
        }

    protected:
        Matrix(void){}
        ~Matrix(void){}

    private:
        T data[dimension];
    };

    //------------------------------------------------------------------
    class Matrix2 : public Matrix<Matrix2, Vec2, 2>
    {
    public:
        Matrix2(void);
        Matrix2(const float v);
        Matrix2(const Vec2 & v);
        Matrix2(const Vec2 & v1, const Vec2 & v2);
        Matrix2(const Matrix2 & copy);

        const float det(void) const;
        float cofactor(int x, int y) const;
        Matrix2 adjugate(void) const;
        Matrix2 inverse(void) const;

    protected:
        // Matrix2(void){}
    private:
    };

    //------------------------------------------------------------------
    class Matrix3 : public Matrix<Matrix3, Vec3, 3>
    {
    public:
        Matrix3(void);
        Matrix3(const float v);
        Matrix3(const Vec3 & v);
        Matrix3(const Vec3 & param1, const Vec3 & param2, const Vec3 & param3);
        Matrix3(const Matrix3 & copy);


        const float det(void) const;
        float cofactor(int x, int y) const;
        Matrix3 adjugate(void) const;
        Matrix3 inverse(void) const;
    };

    //------------------------------------------------------------------
    class Matrix4 : public Matrix<Matrix4, Vec4, 4>
    {
    public: 
        Matrix4(void);
        Matrix4(const float v);
        Matrix4(const Vec4 & v);
        Matrix4(const float s1, const float s2, const float s3, const float s4);
        Matrix4(const Vec4 & v1, const Vec4 & v2, const Vec4 & v3, const Vec4 & v4);
        Matrix4(const Matrix4 & copy);
        
        static Matrix4 CreateTranslationMatrix(const Size3 & size);
        static Matrix4 CreateRotationMatrix(const Vec3 & angle);
        static Matrix4 CreateScaleMatrix(const Vec3 & scale);

        static Matrix4 CreateLookAtMatrix(const Vec3 & position, const Vec3 & target, const Vec3 & world_up);

        static Matrix4 CreateOrthogonalMatrix(const Size2 & viewPortSize, const float near, const float far);
        static Matrix4 CreateProjectionMatrix(const Size2 & viewPortSize, const float near, const float far);

    };
}

#endif //__MATRIX_H__