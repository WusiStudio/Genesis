#include "World.h"
#include <algorithm>
#include "WSLog.h"


namespace engine
{
    using WsTools::Log;

    vector<World *> World::ms_worldPool;
    const char * const World::msc_nodeType = "World";

    const vector<World *> & World::worldPool()
    {
        return ms_worldPool;
    }

    World * World::getWorldById(const string & id)
    {
        for(auto item : ms_worldPool)
        {
            if(item->id() == id)
            {
                return item;
            }
        }
        return nullptr;
    }

    const char *  World::nodeType(void) const
    {
        return msc_nodeType;
    }

    World::World(void)
    {
    }

    World::~World(void)
    {
        auto index = std::find(ms_worldPool.begin(), ms_worldPool.end(), this);
        if(index != ms_worldPool.end())
        {
            ms_worldPool.erase(index);
        }
    }

    const bool World::init()
    {
        if(!Object::init()){ return false; }
        
        ms_worldPool.push_back(this);
        retain();

        return true;
    }

    const bool World::composition(const float dp)
    {
        return tick(dp);
    }

    const bool World::protograph(const Matrix4 & eye_matrix, const Matrix4 & screen_matrix) const
    {
        return draw(eye_matrix, screen_matrix);
    }

    const bool World::append(Node & child)
    {
        return BaseNode::append(child);
    }

    const bool World::remove(Node & child)
    {
        return BaseNode::remove(child);
    }
}