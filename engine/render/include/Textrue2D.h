#pragma once
#ifndef __TEXTRUE_2D_H__
#define __TEXTRUE_2D_H__

#include "Object.h"
#include "Image.h"
#include "Vec.h"
#include <glad/glad.h>
#include <string>

namespace engine
{
    using std::string;

    class Textrue2D : public Object
    {
        PROPERTY_R(GLuint, textrueId);
    public:
        static Textrue2D & Create(const string & file_name);
        static Textrue2D & Create(const Image & img);
        static Textrue2D & Create(const vector<char> & bmp_data, const Size2 & size);

    protected:
        CREATEFUNC(Textrue2D);

        virtual ~Textrue2D();

        virtual const bool init(void) override;
        virtual const bool initWithFineName(const string & file_name);
        virtual const bool initWithImage(const Image & img);
        virtual const bool initWithBmpData(const vector<char> & bmp_data, const Size2 & size);
    };
}

#endif //__TEXTRUE_2D_H__