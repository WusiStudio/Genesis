#pragma once
#ifndef __UUID_H__
#define __UUID_H__

#include "Struct.h"
#include <iostream>
#include <string>

using std::string;
using std::ostream;

namespace engine
{
    namespace tools
    {
        struct Uuid : public Struct
        {
        public:

            
            static Uuid Empty(void);

            Uuid(void);
            Uuid(const Uuid & uuid);
            Uuid(const unsigned char * data);

            ~Uuid(){}

            const string toString(void) const;

            friend ostream & operator<<(ostream & out, const Uuid & uuid);
            const bool operator==(const Uuid & u) const;
        protected:
        private:
            static Uuid * ms_empty;
            unsigned char m_data[16];
        };
    }
}

#endif //__UUID_H__