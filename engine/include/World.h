#pragma once
#ifndef __WORLD_H__
#define __WORLD_H__

#include "BaseNode.h"
#include "Node.h"
#include "CameraInterface.h"
#include <vector>

namespace engine
{
    using std::vector;
    
    class World : public BaseNode, protected CameraInterface
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

        const bool composition(const float dp) override final;
        const bool protograph(const Matrix4 & eye_matrix, const Matrix4 & screen_matrix) const override final;

    private:
        static const char * const msc_nodeType;

        static vector<World *> ms_worldPool;
    };
}

#endif //__WORLD_H__