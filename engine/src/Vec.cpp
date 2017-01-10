#include "Vec.h"
#include <cmath>

namespace engine
{
    float & Vec::operator[](const unsigned int index) const
    {
        return *((float *)this + index);
    }

    //------------------------------------------------------------------
    Vec2::Vec2(void) : Vec2(0.0f) { }

    Vec2::Vec2(const float v) : Vec2(v, v) { }

    Vec2::Vec2(const float x, const float y)
    {
        this->x = x;
        this->y = y;
    }

    Vec2::Vec2(const Vec2 & copy) : Vec2(copy.x, copy.y) { }

    Vec2::~Vec2(void)
    {
        
    }

    const Vec2 Vec2::operator-(void) const
    {
        return Vec2(-x, -y);
    }

    const Vec2 Vec2::operator+(const Vec2 & v) const
    {
        return Vec2(x + v.x, y + v.y);
    }

    Vec2 & Vec2::operator+=(const Vec2 & v)
    {
        x += v.x;
        y += v.y;
        return *this;
    }

    const Vec2 Vec2::operator-(const Vec2 & v) const
    {
        return Vec2(x - v.x, y - v.y);
    }

    Vec2 & Vec2::operator-=(const Vec2 & v)
    {
        x -= v.x;
        y -= v.y;
        return *this;
    }

    const Vec2 Vec2::operator*(const float v) const
    {
        return Vec2(x * v, y * v);
    }

    Vec2 & Vec2::operator*=(const float s)
    {
        x *= s;
        y *= s;
        return *this;
    }

    const Vec2 Vec2::operator/(const float s) const
    {
        return Vec2(x / s, y / s);
    }

    Vec2 & Vec2::operator/=(const float s)
    {
        x /= s;
        y /= s;
        return *this;
    }

    const Vec2 operator*(const float s, const Vec2 & v)
    {
        return Vec2(v.x * s, v.y * s);
    }

    ostream & operator<<(ostream & _stream, const Vec2 & param)
    {
         _stream << "Vec2(" <<  param.x << ", " << param.y << ")";
         return _stream;
    }

    const float Vec2::dot(const Vec2 & v) const
    {
        return x * v.x + y * v.y;
    }

    const float Vec2::modulo(void) const
    {
        return sqrt(dot(*this));
    }

    const float Vec2::angle(const Vec2 & v) const
    {
        return acos(dot(v) / modulo() / v.modulo()) / PI * 180;
    }

    const Vec2 Vec2::normalize(void) const
    {
        return operator/(modulo());
    }

    //------------------------------------------------------------------
    Vec3::Vec3(void) : Vec3(0.0f) { }

    Vec3::Vec3(const float v) : Vec3(v, v, v) { }

    Vec3::Vec3(const float x, const float y) : Vec3(x, y, 0.0f) { }

    Vec3::Vec3(const float x, const float y, const float z) : Vec2(x, y)
    {
        this->z = z; 
    }

    Vec3::Vec3(const Vec2 & copy) : Vec3(copy.x, copy.y) { }

    Vec3::Vec3(const Vec3 & copy) : Vec3(copy.x, copy.y, copy.z) { }

    const Vec3 Vec3::operator+(const Size3 & offset) const
    {
        return Vec3(x + offset.width, y + offset.height, z + offset.depth);
    }

    const Vec3 & Vec3::operator+=(const Size3 & offset)
    {
        x += offset.width;
        y += offset.height;
        z += offset.depth;
        return *this;
    }

    const Size3 Vec3::operator-(const Vec3 & v) const
    {
        return Size3(x - v.x, y - v.y, z - v.z);
    }

    const Vec3 Vec3::operator-(const Size3 & offset) const
    {
        return Vec3(x - offset.width, y - offset.height, z - offset.depth);
    }

    const Vec3 & Vec3::operator-=(const Size3 & offset)
    {
        x -= offset.width;
        y -= offset.height;
        z -= offset.depth;
        return *this;
    }

    const Vec3 Vec3::operator*(const float s) const
    {
        return Vec3(x * s, y * s, z * s);
    }

    const Vec3 Vec3::operator*(const Vec3 & v) const
    {
        return Vec3(x * v.x, y * v.y, z * v.z);
    }

    const Vec3 & Vec3::operator*=(const float s)
    {
        x *= s;
        y *= s;
        z *= s;
        return *this;
    }

    const Vec3 Vec3::operator/(const float s) const
    {
        return Vec3(x / s, y / s, z / s);
    }

    const Vec3 & Vec3::operator/=(const float s)
    {
        x /= s;
        y /= s;
        z /= s;
        return *this;
    }

    const Vec3 Vec3::operator-(void) const
    {
        return Vec3(-x, -y, -z);
    }

    const bool Vec3::operator==(const Vec3 & v) const
    {
        return equal(x, v.x) && equal(y, v.y) && equal(z, v.z);
    }

    const Vec3 operator*(const float s, const Vec3 & v)
    {
        return Vec3(v.x * s, v.y * s, v.z * s);
    }

    ostream & operator<<(ostream & _stream, const Vec3 & v)
    {
        _stream << "Vec3(" << v.x << ", " << v.y << ", " << v.z << ")";
        return _stream;
    }

    Size3 Vec3::convertToSize3(void) const
    {
        return Size3(x, y, z);
    }

    const float Vec3::dot(const Vec3 & v) const
    {
        return x * v.x + y * v.y + z * v.z;
    }

    const Vec3 Vec3::cross(const Vec3 & v) const
    {
        return Vec3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
    }

    const float Vec3::modulo(void) const
    {
        return sqrt(dot(*this));
    }

    const Vec3 Vec3::normalize(void) const
    {
        return operator/(modulo());
    }

    Vec3::~Vec3(void)
    {
        
    }

    //------------------------------------------------------------------
    Vec4::Vec4(void) : Vec4(0.0f) { }

    Vec4::Vec4(const float v) : Vec4(v, v, v, v) { }

    Vec4::Vec4(const float x, const float y) : Vec4(x, y, 0.0f) { }

    Vec4::Vec4(const float x, const float y, const float z) : Vec4(x, y, z, 1.0f) { }

    Vec4::Vec4(const float x, const float y, const float z, const float w) : Vec3(x, y, z)
    {
        this->w = w;
    }

    Vec4::Vec4(const Vec3 & copy) : Vec4(copy.x, copy.y, copy.z) { }

    Vec4::Vec4(const Vec3 & v, const float s) : Vec4(v)
    {
        w = s;
    }

    Vec4::Vec4(const Vec4 & copy) : Vec4(copy.x, copy.y, copy.z, copy.w) { }

    ostream & operator<<(ostream & _stream, const Vec4 & param)
    {
        _stream << "Vec4(" << param.x << ", " << param.y << ", " << param.z << ", " << param.w << ")";
        return _stream;
    }

    Vec4::~Vec4(void)
    {
        
    }


    //------------------------------------------------------------------
    Size2::Size2(void) : Size2(0.0f) { }
    
    Size2::Size2(const float v) : Size2(v, v) { }

    Size2::Size2(const float width, const float height)
    {
        this->width = width;
        this->height = height;
    }

    Size2::Size2(const Size2 & copy) : Size2(copy.width, copy.height) { }

    const Size2 Size2::operator+(const Size2 & param) const
    {
        return Size2(width + param.width, height + param.height);
    }

    const Size2 Size2::operator-(const Size2 & param) const
    {
        return Size2(width - param.width, height - param.height);
    }

    ostream & operator<<(ostream & _stream, const Size2 & param)
    {
        _stream << "Szie2(" << param.width << ", " << param.height <<")";
        return _stream;
    }


    //------------------------------------------------------------------
    Size3::Size3(void) : Size3(0.0f) { }

    Size3::Size3(const float v) : Size3(v, v, v){ }

    Size3::Size3(const float width, const float height) : Size3(width, height, 0.0f) { }

    Size3::Size3(const float width, const float height, const float depth) : Size2(width, height)
    {
        this->depth = depth;
    }

    Size3::Size3(const Size3 & copy) : Size3(copy.width, copy.height, copy.depth) { }

    Size3::Size3(const Size2 & copy) : Size3(copy.width, copy.height) { }

    const Size3 Size3::operator+(const Size3 & param) const
    {
        return Size3(width + param.width, height + param.height, depth + param.depth);
    }

    const Size3 Size3::operator-(const Size3 & param) const
    {
        return Size3(width - param.width, height - param.height, depth + param.depth);
    }

    ostream & operator<<(ostream & _stream, const Size3 & param)
    {
        _stream << "Size3(" << param.width << ", " << param.height << ", " << param.depth << ")";
        return _stream;
    }

}