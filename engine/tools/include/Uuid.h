#pragma once
#ifndef __UUID_H__
#define __UUID_H__

#include "Object.h"
#include <iostream>
#include <string>

using namespace std;

namespace engine
{
    namespace tools
    {
        class Uuid : public Object
        {
        public:
            CREATEFUNC(Uuid);
            static Uuid & Create(const Uuid & _uuid);

            const string toString(void) const;

            friend ostream & operator<<(ostream & _out, const Uuid & _uuid);
        protected:
            Uuid();
            const bool init(void) override;
            virtual const bool init(const Uuid & _uuid);
        private:
            unsigned short _data[16];
        };
    }
}

#endif //__UUID_H__