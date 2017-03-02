#include "Uuid.h"
#include <cstring>
#include <random>

using std::random_device;
using std::uniform_int_distribution;

namespace engine
{
    namespace tools
    {

        Uuid * Uuid::ms_empty = nullptr;
        Uuid Uuid::Empty(void)
        {
            if(!ms_empty)
            {
                ms_empty = new Uuid();
                memset(ms_empty->m_data, 0, sizeof(ms_empty->m_data));
            }
            return *ms_empty;
        }

        Uuid::Uuid(void)
        {
            for(size_t i = 0; i < sizeof(m_data) / sizeof(unsigned char); ++i)
            {
                random_device rd;
                uniform_int_distribution<int> dis(0x00, 0xFF);
                m_data[i] = dis(rd);
            }
        }

        Uuid::Uuid(const Uuid & uuid)
        {
            memcpy(m_data, uuid.m_data, sizeof(uuid.m_data));
        }

        Uuid::Uuid(const unsigned char * data)
        {
            memcpy(m_data, data, sizeof(m_data));
        }

        const string Uuid::toString(void) const
        {
            char temp[33] = {0};
            for(size_t i = 0; i < 16; ++i)
            {
                sprintf(temp + 2 * i, "%02X", m_data[i]);
            }
            return temp;
        }

        ostream & operator<< (ostream & out, const Uuid & uuid)
        {
            return out << uuid.toString();
        }

        const bool Uuid::operator==(const Uuid & u) const
        {
            for(size_t i = 0; i < sizeof(m_data) / sizeof(unsigned char); ++i)
            {
                if(m_data[i] != u.m_data[i]) return false;
            }

            return true;
        }
    }
}