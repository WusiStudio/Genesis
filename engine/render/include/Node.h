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
        PROPERTY_R(Vec3, position);
        PROPERTY_R(Vec3, rotate);
        PROPERTY_R(Vec3, scale);
    public:
    
        CREATEFUNC(Node);
        //类型
        virtual const char * nodeType(void) const override final;
        
        //添加子元素
        const bool append(Node & child);

        //删除子元素
        const bool remove(Node & child);

        //位置
        virtual void position(const Vec3 & v);

        //旋转
        virtual void rotate(const Vec3 & v);

        //缩放
        virtual void scale(const Vec3 & v);
        
        //将当前坐标转为世界坐标
        const Vec3 convertToWorldSpace(const Vec3 & v);
        //将世界坐标转换为当前坐标
        const Vec3 convertToNodeSpace(const Vec3 & v);
        
    protected:
        Node(void);
        virtual ~Node(void);
        virtual const bool init(void) override;

        const Size3 accumulativeRotateOffset(void) const;
        const Size3 accumulativeScaleOffset(void) const;
        const Size3 worldCoordinateOffset(void) const;

        virtual const bool tick(const float dt) override;
        
    private:

        //计算世界坐标系位置
        const Vec3 calculateWorldCoordinate(void);
        
        //标记世界坐标无效
        void worldCoordinateInvalid(void);

        //所有后代的世界坐标设为无效
        void posterityWorldCoordinateInvalid(void);


        static const char * const msc_nodeType;

        //累计旋转  累计缩放
        Vec3 m_accumulativeRotate, m_accumulativeScale;

        //世界坐标
        Vec3 m_worldCoordinate;
        //世界坐标是否有效
        bool m_worldCoordinateInvalid;        
    };
}

#endif //__NODE_H__