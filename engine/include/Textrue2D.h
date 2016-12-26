#pragma once
#ifndef __TEXTRUE_2D_H__
#define __TEXTRUE_2D_H__

#include "Object.h"
#include "Image.h"
#include <glad/glad.h>
#include <string>

namespace engine
{
    using std::string;

    class Textrue2D : public Object
    {
    public:
        static Textrue2D & Create(const string & fileName);
        static Textrue2D & Create(const Image & img);

        const int textrueId(void) const;
    protected:
        CREATEFUNC(Textrue2D);

        const bool init(void) override;
        virtual const bool init(const string & fileName);
        virtual const bool init(const Image & img);
    private:
        GLuint m_textrueId;
    };
}

#endif //__TEXTRUE_2D_H__