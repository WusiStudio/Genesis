#pragma once
#ifndef __NODE_H__
#define __NODE_H__

#include "BaseNode.h"
#include "Vec.h"
#include "Matrix.h"

#include <string>

namespace engine
{
    using std::string;
    
    class Node : public BaseNode
    {
    public:
        
        CREATEFUNC(Node);

        //类型
        const char * nodeType(void) const override final;
        
        //添加子元素
        const bool append(Node & child);

        //删除子元素
        const bool remove(Node & child);

        //位置
        void position(const Vec3 & v);
        const Vec3 & position(void) const;

        //旋转
        void rotate(const Vec3 & v);
        const Vec3 & rotate(void) const;

        //缩放
        void scale(const Vec3 & v);
        const Vec3 & scale(void) const;
        
        //将当前坐标转为世界坐标
        const Vec3 convertToWorldSpace(const Vec3 & v);
        //将世界坐标转换为当前坐标
        const Vec3 convertToNodeSpace(const Vec3 & v);
        
    protected:
        Node(void);
        virtual ~Node(void);
        const bool init(void) override;

        const Size3 accumulativeRotateOffset(void) const;
        const Size3 accumulativeScaleOffset(void) const;
        const Size3 worldCoordinateOffset(void) const;

        const bool tick(const float dt) override;
        
    private:

        //计算世界坐标系位置
        const Vec3 calculateWorldCoordinate(void);
        
        //标记世界坐标无效
        void worldCoordinateInvalid(void);

        //所有后代的世界坐标设为无效
        void posterityWorldCoordinateInvalid(void);


        static const char * const msc_nodeType;

        //位置 旋转 缩放
        Vec3 m_position, m_rotate, m_scale;

        //累计旋转  累计缩放
        Vec3 m_accumulativeRotate, m_accumulativeScale;

        //世界坐标
        Vec3 m_worldCoordinate;
        //世界坐标是否有效
        bool m_worldCoordinateInvalid;        
    };
}

#endif //__NODE_H__