#include "Object.h"
#include "Gc.h"

namespace engine
{
    const bool Object::ready(void) const
    {
        return !m_initializeErrorCode;
    }

    const int Object::fault(void) const
    {
        return m_initializeErrorCode;
    }

    const bool Object::autoRelease(void)
    {
        return Gc::Instance().watch(*this);
    }

    const bool Object::init(void)
    {
        m_initializeErrorCode = 0;
        return true;
    }

    void Object::initializeError(const int error_code)
    {
        if(!error_code){ return; }
        m_initializeErrorCode = error_code;
    }
}
