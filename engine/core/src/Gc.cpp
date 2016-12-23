#include "Gc.h"

#include <algorithm>

using namespace std;

namespace engine
{
    Gc & Gc::Instance(void)
    {
        static Gc * s_instance = new Gc();
        return * s_instance;
    }

    Gc::Gc(void)
    {
        m_objectPool = new list<BaseObject *>();
    }

    Gc::~Gc(void)
    {
        cleanAll();
        delete m_objectPool;
    }

    void Gc::clean(void)
    {
        for(auto item = m_objectPool->begin(); item != m_objectPool->end(); ++item)
        {
            if((*item)->quoteCount() <= 0)
            {
                BaseObject * temp = (*item);
                delete temp;
                item--;
                m_objectPool->remove(temp);
            }
        }
    }

    const bool Gc::watch(Object & obj)
    {
        BaseObject * watchObj = (BaseObject *)&obj;
        if(find(m_objectPool->begin(), m_objectPool->end(), watchObj) == m_objectPool->end())
        {
            return false;
        }

        m_objectPool->push_back(watchObj);
        return true;
    }


    void Gc::cleanAll(void)
    {
        for(auto item = m_objectPool->begin(); item != m_objectPool->end(); ++item)
        {
            BaseObject * temp = (*item);
            delete temp;
            item--;
            m_objectPool->remove(temp);
        }
    }
}
