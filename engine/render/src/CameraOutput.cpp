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
        m_camera->viewPortSize(m_size);
    }

    void CameraOutput::size(const Size2 & size)
    {
        m_size = size;
        if(m_camera)
        {
            m_camera->viewPortSize(m_size);
        }
    }
    
    const bool CameraOutput::tick(const float dt)
    {
        if(!Node::tick(dt)){ return false; }

        if(!m_camera){ return true; }

        return composition(dt);
    }

    const bool CameraOutput::draw(const Matrix4 & eye_matrix, const Matrix4 & screen_matrix) const
    {
        //拍照   (应该传屏幕大小信息)
        if(!protograph(Matrix4::CreateTranslationMatrix(size()), m_coordinate == CoordinateSystem::Screen ? Matrix4::CreateTranslationMatrix(Size3(-1.0f, -1.0f, .0f)) : Matrix4(1.0f))){ return false; }

        //绘制子元素
        if(!Node::draw(eye_matrix, screen_matrix)){ return false; }

        return true;
    }

    const bool CameraOutput::composition(const float dp)
    {
        return ((CameraInterface *)m_camera)->composition(dp);
    }

    const bool CameraOutput::protograph(const Matrix4 & eye_matrix, const Matrix4 & screen_matrix) const 
    {
        if(!m_camera){ return true; }

        return ((CameraInterface *)m_camera)->protograph(eye_matrix, screen_matrix);
    }

    CameraOutput::CameraOutput(void)
    {
        m_camera = nullptr;
        m_coordinate = CoordinateSystem::OpenGL;
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