#pragma once
#ifndef __BASE_CAMERA_H__
#define __BASE_CAMERA_H__

#include "Matrix.h"

//interfce

namespace engine
{
    class CameraInterface
    {
    public:
        virtual const bool composition(const float dp) = 0;
        virtual const bool protograph(const Matrix4 & eye_matrix, const Matrix4 & screen_matrix) const = 0;
    protected:
    };
}

#endif //__BASE_CAMERA_H__