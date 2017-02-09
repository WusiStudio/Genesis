#include "Uuid.h"
#include <cstring>
#include <random>

using std::random_device;
using std::uniform_int_distribution;

namespace engine
{
    namespace tools
    {
        Uuid & Uuid::Create(const Uuid & _uuid)
        {
            Uuid & result = Create();
            bool uuidInit = result.init(_uuid);

            assert(uuidInit);

            if(!uuidInit){ result.initializeError(1); }
            return result;
        }

        const bool Uuid::init(void)
        {
            if(!Object::init()){ return false; }
            
            for(size_t i = 0; i < sizeof(_data) / sizeof(unsigned short); ++i)
            {
                random_device rd;
                uniform_int_distribution<int> dis(0x00, 0xFF);
                _data[i] = dis(rd);
            }
            return true;
        }

        const bool Uuid::init(const Uuid & _uuid)
        {
            memcpy(_data, _uuid._data, sizeof(_uuid._data));

            return true;
        }

        const string Uuid::toString(void) const
        {
            char temp[33] = {0};
            for(unsigned short i = 0; i < 16; ++i)
            {
                sprintf(temp + 2 * i, "%02X", _data[i]);
            }
            return temp;
        }

        ostream & operator<< (ostream & _out, const Uuid & _uuid)
        {
            return _out << _uuid.toString();
        }

        Uuid::Uuid()
        {
            memset(_data, 0, sizeof(_data));
        }
    }
}