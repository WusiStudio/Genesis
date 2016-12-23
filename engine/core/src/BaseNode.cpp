#include "BaseNode.h"

#include <algorithm>

using namespace std;

namespace engine
{

    BaseNode::BaseNode(void)
    {
        m_id = nullptr;
        m_parent = nullptr;
    }

    BaseNode::~BaseNode(void)
    {
        if(m_id) delete m_id;
    }

    void BaseNode::id(const string & id)
    {
        if(m_id) delete m_id;
        m_id = new string(id);
    }

    string BaseNode::id(void) const
    {
        return m_id == nullptr ? "" : *m_id;
    }

    BaseNode & BaseNode::root(void)
    {
        BaseNode * result = this;

        while(result->m_parent)
        {
            result = result->m_parent;
        }

        return * result;
    }

    const bool BaseNode::remove(void)
    {
        if(!m_parent) return false;

        return m_parent->remove(*this);
    }

    BaseNode * BaseNode::parent(void) const
    {
        return m_parent;
    }


    const bool BaseNode::clear(void)
    {
        while(!m_chidren.empty())
        {
            auto item = m_chidren.front();
            item->release();
            item->m_parent = nullptr;
            m_chidren.pop_front();
        }

        return m_chidren.empty();
    }

    BaseNode * BaseNode::find(const string & id)
    {
        BaseNode * result = nullptr;

        for(auto item : m_chidren)
        {
            if(item->id() == id)
            {
                result = item;
                break;
            }
        }

        return result;
    }

    void BaseNode::each(function<bool(BaseNode & node)> cb) const
    {
        for(auto item : m_chidren)
        {
            if(cb(*item)) break;
        }
    }

    void BaseNode::onTick(function<void(const float)> on_tick)
    {
        if(on_tick) m_onTick = on_tick;
    }

    const bool BaseNode::init(void)
    {
        if(!Object::init())
        {
            return false;
        }
        
        return true;
    }

    const bool BaseNode::append(BaseNode & child)
    {
        bool prepare = !child.m_parent || child.remove();

        assert(prepare);

        if(prepare){
            m_chidren.push_back(&child);
            child.m_parent = this;
            child.retain();
        }

        return prepare;
    }

    const bool BaseNode::remove(BaseNode & child)
    {
        bool result = false;
        auto item = m_chidren.begin();
        while(item != m_chidren.end())
        {
            if(*item == &child)
            {
                (*item)->release();
                (*item)->m_parent = nullptr;
                item = m_chidren.erase(item);
                result = true;
                break;
            }
            item++;
        }
        return result;
    }


    function<void(const float)> BaseNode::onTick(void) const
    {
        return m_onTick;
    }

    const bool BaseNode::tick(const float dt)
    {
        for(auto item : m_chidren)
        {
            if(item->onTick()) item->onTick()(dt);
            if(!item->tick(dt))
            {
                return false;
            }
        }
        return true;
    }

    const bool BaseNode::draw(const Matrix4 & projection)
    {
        for(auto item : m_chidren)
        {
            if(!item->draw(projection))
            {
                return false;
            }
        }
        return true;
    }
    
}