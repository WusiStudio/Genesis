#pragma once
#ifndef __BASE_CAMERA_H__
#define __BASE_CAMERA_H__

//interfce

namespace engine
{
    class CameraInterface
    {
    public:
        virtual const bool composition(const float dp) = 0;
        virtual const bool protograph(void) const = 0;
    protected:
    };
}

#endif //__BASE_CAMERA_H__