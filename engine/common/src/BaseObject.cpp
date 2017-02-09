#include "BaseObject.h"

namespace engine
{
    BaseObject::BaseObject(void)
    {
        m_quoteCount = 0;
    }

    void BaseObject::retain(void)
    {
        ++ m_quoteCount;
    }

    void BaseObject::release(void)
    {
        -- m_quoteCount;
    }
}