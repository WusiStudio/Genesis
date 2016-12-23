#include "Object.h"
#include "Gc.h"

namespace engine
{
    const bool Object::ready(void) const
    {
        return !m_initializeErrorCode;
    }

    const unsigned short Object::fault(void) const
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

    void Object::initializeError(const unsigned short errorCode)
    {
        if(!errorCode){ return; }
        m_initializeErrorCode = errorCode;
    }
}
