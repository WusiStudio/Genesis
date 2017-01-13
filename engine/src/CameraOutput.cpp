#include "CameraOutput.h"
#include "WSLog.h"

namespace engine
{
    using WsTools::Log;

    const bool CameraOutput::init(void)
    {
        if(!Node::init()){ return false; }
        return true;
    }

    Camera & CameraOutput::camera(void) const
    {
        return *m_camera;
    }
    
    void CameraOutput::camera(Camera & linkCamera)
    {
        if(m_camera)
        {
            m_camera->release();
            m_camera = nullptr;
        }
        m_camera = &linkCamera;
        m_camera->retain();
    }

    void CameraOutput::size(const Size2 & size)
    {
        m_size = size;
    }

    const Size2 & CameraOutput::size(void) const
    {
        return m_size;
    }

    const bool CameraOutput::tick(const float dt)
    {
        if(!Node::tick(dt)){ return false; }

        if(!m_camera){ return true; }

        return composition(dt);
    }

    const bool CameraOutput::draw(const Matrix4 & eyeMatrix, const Matrix4 & screenMatrix) const
    {

        //拍照   (应该传屏幕大小信息)
        if(protograph(Matrix4(1.0f), Matrix4(1.0f))){ return false; }

        //绘制子元素
        if(!Node::draw(eyeMatrix, screenMatrix)){ return false; }

        return true;
    }

    const bool CameraOutput::composition(const float dp)
    {
        return ((CameraInterface *)m_camera)->composition(dp);
    }

    const bool CameraOutput::protograph(const Matrix4 & eyeMatrix, const Matrix4 & screenMatrix) const 
    {
        if(!m_camera){ return true; }

        return ((CameraInterface *)m_camera)->protograph(eyeMatrix, screenMatrix);
    }

    CameraOutput::CameraOutput(void)
    {
        m_camera = nullptr;
    }

    CameraOutput::~CameraOutput(void)
    {
        if(m_camera)
        {
            m_camera->release();
            m_camera = nullptr;
        }
    }
}