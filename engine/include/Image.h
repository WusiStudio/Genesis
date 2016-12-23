#pragma once
#ifndef __IMAGE_H__
#define __IMAGE_H__

#include "Object.h"
#include <string>

using std::string;

namespace engine
{
    class Image : public Object
    {
    public:
        static Image & Create(const string & path);

        const int width(void) const;
        const int height(void) const;
        unsigned char * data(void) const;
        
    protected:
        const bool init(void) override;
        virtual const bool init(const string & path);
        Image(void);
        virtual ~Image(void);
    private:
        CREATEFUNC(Image);

        int m_width, m_height, m_n;
        unsigned char * m_data;
    };
}

#endif //__IMAGE_H__