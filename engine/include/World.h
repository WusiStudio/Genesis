#pragma once
#ifndef __WORLD_H__
#define __WORLD_H__

#include "BaseNode.h"
#include "Camera.h"
#include <vector>

namespace engine
{
    using std::vector;
    
    class World : public BaseNode
    {
    public:

        CREATEFUNC(World);
        static const vector<World *> & worldPool();

        //类型
        const char *  nodeType(void) const override final;

        //添加子节点
        const bool append(Node & child);
        //删除子节点
        const bool remove(Node & child);
        
    protected:
        World(void);
        ~World(void);
        const bool init(void) override;

    private:
        static const char * const ms_nodeType;

        static vector<World *> ms_worldPool;
    };
}

#endif //__WORLD_H__