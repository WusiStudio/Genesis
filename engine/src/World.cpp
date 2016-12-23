#include "World.h"
#include <algorithm>
#include "WSLog.h"


namespace engine
{
    using WsTools::Log;

    vector<World *> World::ms_worldPool;
    const char * const World::ms_nodeType = "World";

    const vector<World *> & World::worldPool()
    {
        return ms_worldPool;
    }

    const char *  World::nodeType(void) const
    {
        return ms_nodeType;
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

    const bool World::append(Node & child)
    {
        return BaseNode::append(child);
    }

    const bool World::remove(Node & child)
    {
        return BaseNode::remove(child);
    }
}