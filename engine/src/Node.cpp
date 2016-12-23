#include "Node.h"
#include "WSLog.h"
#include "Matrix.h"

namespace engine
{
    using WsTools::Log;

    const char * const Node::msc_nodeType = "Node";

    Node::Node(void)
    {
        m_scale = Vec3(1.0f);
        m_accumulativeScale = Vec3(1.0f);
    }

    Node::~Node(void)
    {
        
    }

    const bool Node::init(void)
    {
        if(!Object::init()){ return false; }

        worldCoordinateInvalid();
        return true;
    }

    const char *  Node::nodeType(void) const
    {
        return msc_nodeType;
    }

    const bool Node::append(Node & child)
    {
        return BaseNode::append(child);
    }

    const bool Node::remove(Node & child)
    {
        return BaseNode::remove(child);
    }

    void Node::position(const Vec3 & v)
    {
        m_position = v;
        worldCoordinateInvalid();
    }

    const Vec3 & Node::position(void) const
    {
        return m_position;
    }

    void Node::rotate(const Vec3 & v)
    {
        m_rotate = v;
        posterityWorldCoordinateInvalid();
    }

    const Vec3 & Node::rotate(void) const
    {
        return m_rotate;
    }

    void Node::scale(const Vec3 & v)
    {
        m_scale = v;
        posterityWorldCoordinateInvalid();
    }

    const Vec3 & Node::scale(void) const
    {
        return m_scale;
    }

    const Vec3 Node::convertToWorldSpace(const Vec3 & v)
    {
        return calculateWorldCoordinate() + v.convertToSize3();
    }

    const Vec3 Node::convertToNodeSpace(const Vec3 & v)
    {
        return v - calculateWorldCoordinate().convertToSize3();
    }

    const Vec3 Node::calculateWorldCoordinate(void)
    {
        if(m_worldCoordinateInvalid){ return m_worldCoordinate; }
        m_worldCoordinate = m_position;
        if(!parent() || parent()->nodeType() != msc_nodeType){ return m_worldCoordinate; }

        Node & parentNode = *(Node *)parent();

        //世界坐标偏移
        Size3 worldCoordinateOffset = parentNode.calculateWorldCoordinate().convertToSize3();

        //累计旋转   //累计缩放  //累计平移(也就是父级世界坐标)
        m_accumulativeRotate = parentNode.m_accumulativeRotate + parentNode.rotate().convertToSize3();
        m_accumulativeScale = parentNode.m_accumulativeScale * parentNode.scale();

        //旋转
        Matrix4 rotationMatrix = Matrix4::CreateRotationMatrix(m_accumulativeRotate);
        //缩放
        Matrix4 scaleMatrix = Matrix4::CreateScaleMatrix(m_accumulativeScale);
        //平移
        Matrix4 translationMatrix = Matrix4::CreateTranslationMatrix(worldCoordinateOffset);

        //累计旋转  × 累计缩放 ×  累计平移 × 局域坐标 = 模型世界坐标
        m_worldCoordinate = rotationMatrix * scaleMatrix * translationMatrix * Vec4(m_position, 1.0);

        //当前世界坐标有效
        m_worldCoordinateInvalid = true;
        return m_worldCoordinate;
    }

    void Node::worldCoordinateInvalid(void)
    {
        m_worldCoordinateInvalid = false;
        posterityWorldCoordinateInvalid();
    }

    void Node::posterityWorldCoordinateInvalid(void)
    {
        each([](BaseNode & item)->bool{
            ((Node &)item).worldCoordinateInvalid();
            return true;
        });
    }

    const Size3 Node::accumulativeRotateOffset(void) const 
    {
        return m_accumulativeRotate.convertToSize3();
    }

    const Size3 Node::accumulativeScaleOffset(void) const 
    {
        return m_accumulativeScale.convertToSize3();
    }

    const Size3 Node::worldCoordinateOffset(void) const 
    {
        return m_worldCoordinate.convertToSize3();
    }

    const bool Node::tick(const float dt)
    {
        //计算运动区间

        //更新世界坐标系位置
        calculateWorldCoordinate();

        return BaseNode::tick(dt);
    }
}