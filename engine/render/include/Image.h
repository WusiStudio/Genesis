#pragma once
#ifndef __IMAGE_H__
#define __IMAGE_H__

#include "Object.h"
#include <string>
#include <vector>

namespace engine
{
    using std::string;
    using std::vector;

    class Image : public Object
    {
        PROPERTY_R(int, width);
        PROPERTY_R(int, height);
        PROPERTY_R(const unsigned char *, data);
    public:
        static Image & Create(const string & path);
        static Image & Create(const vector<char> & binary_data);
    protected:
        virtual const bool init(void) override;
        virtual const bool initWithPath(const string & path);
        virtual const bool initWidthBinaryData(const vector<char> & binary_data);
        Image(void);
        virtual ~Image(void);
    private:
        CREATEFUNC(Image);

        int m_n;
    };
}

#endif //__IMAGE_H__