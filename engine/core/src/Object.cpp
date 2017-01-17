#include "Object.h"
#include "Gc.h"

namespace engine
{
    const bool Object::ready(void) const
    {
        return !m_initializeError;
    }

    const int Object::fault(void) const
    {
        return m_initializeError;
    }

    const bool Object::autoRelease(void)
    {
        return Gc::Instance().watch(*this);
    }

    const bool Object::init(void)
    {
        m_initializeError = 0;
        return true;
    }
}
