#pragma once
#ifndef __IMAGE_H__
#define __IMAGE_H__

#include "Object.h"
#include <string>

namespace engine
{
    using std::string;

    class Image : public Object
    {
    public:
        static Image & Create(const string & path);

        PROPERTY_R(int, width);
        PROPERTY_R(int, height);
        PROPERTY_R(const unsigned char *, data);
    protected:
        const bool init(void) override;
        virtual const bool init(const string & path);
        Image(void);
        virtual ~Image(void);
    private:
        CREATEFUNC(Image);

        int m_n;
    };
}

#endif //__IMAGE_H__