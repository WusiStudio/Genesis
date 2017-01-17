#pragma once 
#ifndef __VEC_H__
#define __VEC_H__

#include "Struct.h"
#include <iostream>

namespace engine
{
    using std::iostream;
    using std::ostream;
    using std::cout;
    using std::endl;
    
    class Vec : public Struct
    {
    public: 
        float & operator[](const unsigned int index) const;
    protected:
        Vec(void){}
        ~Vec(void){}
    };

    typedef struct Size2 SIZE2;
    typedef struct Size3 SIZE3;

    //------------------------------------------------------------------
    struct Vec2 : public Vec
    {
    public:
        Vec2(void);
        Vec2(const float v);
        Vec2(const float x, const float y);
        Vec2(const Vec2 & copy);
        
        ~Vec2(void);
        
        
        //重载运算符
        const Vec2 operator-(void) const;

        const Vec2 operator+(const Vec2 & v) const;
        Vec2 & operator+=(const Vec2 & v);

        const Vec2 operator-(const Vec2 & v) const;
        Vec2 & operator-=(const Vec2 & v);
        
        const Vec2 operator*(const float s) const;
        Vec2 & operator*=(const float s);

        const Vec2 operator/(const float s) const;
        Vec2 & operator/=(const float s);
        
        friend const Vec2 operator*(const float s, const Vec2 & v);
        friend ostream & operator<<(ostream & _stream, const Vec2 & param);
        
        //点积
        const float dot(const Vec2 & v) const;
        
        //模
        const float modulo(void) const;
        
        //角度
        const float angle(const Vec2 & v) const;

        //标准化
        const Vec2 normalize(void) const;
        
        float x, y;
    };

    //------------------------------------------------------------------
    struct Vec3 : public Vec2
    {
    public:
        Vec3(void);
        Vec3(const float v);
        Vec3(const float x, const float y);
        Vec3(const float x, const float y, const float z);
        
        Vec3(const Vec2 & copy);
        Vec3(const Vec3 & copy);
        
        ~Vec3(void);
        
        //重载运算符
        // const Vec3 operator+(const float s) const;
        const Vec3 operator+(const Size3 & offset) const;
        const Vec3 & operator+=(const Size3 & offset);
        // const Vec3 operator-(const float s) const;
        const Size3 operator-(const Vec3 & v) const;
        const Vec3 operator-(const Size3 & offset) const;
        const Vec3 & operator-=(const Size3 & offset);

        const Vec3 operator*(const float s) const;
        const Vec3 operator*(const Vec3 & v) const;

        const Vec3 & operator*=(const float s);
        const Vec3 operator/(const float s) const;
        const Vec3 & operator/=(const float s);

        const Vec3 operator-(void) const;
        const bool operator==(const Vec3 & v) const;
        
        //这个乘法好像没意义  暂留
        friend const Vec3 operator*(const float s, const Vec3 & v);
        friend ostream & operator<<(ostream & _stream, const Vec3 & v);

        SIZE3 convertToSize3(void) const;
        
        //点积
        const float dot(const Vec3 & v) const;
        
        //叉积
        const Vec3 cross(const Vec3 & v) const;
        
        //模
        const float modulo(void) const;

        //标准化
        const Vec3 normalize(void) const;
        
        float z;
    };

    //------------------------------------------------------------------
    struct Vec4 : public Vec3
    {
    public:
        Vec4(void);
        Vec4(const float v);
        Vec4(const float x, const float y);
        Vec4(const float x, const float y, const float z);
        Vec4(const float x, const float y, const float z, const float w);
        
        Vec4(const Vec3 & copy);
        Vec4(const Vec4 & copy);

        Vec4(const Vec3 & v, const float s);

        friend ostream & operator<<(ostream & _stream, const Vec4 & param);
        
        ~Vec4(void); 
        
        float w;
    };

    //------------------------------------------------------------------
    struct Size2 : public Vec
    {
    public:

        Size2(void);
        Size2(const float v);
        Size2(const float width, const float height);
        Size2(const Size2 & copy);


        const Size2 operator+(const Size2 & param) const;
        const Size2 operator-(const Size2 & param) const;

        const Size2 operator*(const float v) const;
        const Size2 operator/(const float v) const;

        friend ostream & operator<<(ostream & _stream, const Size2 & param); 

        float width, height;
    };

    //------------------------------------------------------------------
    struct Size3 : public Size2
    {
    public:
        Size3(void);
        Size3(const float v);
        Size3(const float _width, const float _height);
        Size3(const float _width, const float _height, const float _depth);
        Size3(const Size3 & copy);
        Size3(const Size2 & copy);

        Vec3 convertToVec3(void) const;

        const Size3 operator+(const Size3 & param) const;
        const Size3 operator-(const Size3 & param) const;

        const Size3 operator*(const float v) const;
        const Size3 operator/(const float v) const;

        friend ostream & operator<<(ostream & _stream, const Size3 & param);
        
        float depth;
    };
}

#endif //__VEC_H__