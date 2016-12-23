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

    Size2 & CameraOutput::size(void)
    {
        return m_size;
    }

    const bool CameraOutput::tick(const float dt)
    {
        if(!Node::tick(dt)){ return false; }

        if(!m_camera){ return false; }

        Log.info("CameraOutput position: {0}, size: {1}", position(), size());

        // return camera().preparatory(dt);
        // return window.tick();
        return true;
    }

    const bool CameraOutput::draw(const Matrix4 & projection)
    {

        //画布空间
        if(!Node::draw(projection)){ return false; }

        if(!m_camera){ return false; }

        //设置摄像机投影到gl空间的位置

        Matrix4 canvasMatrix(1.0f);
        canvasMatrix[0][0] = 2 / size().width;
        canvasMatrix[0][3] = -1.0f;
        canvasMatrix[1][1] = 2 / size().height;
        canvasMatrix[1][3] = -1.0f;

        //拍照
        return true;
        // return camera().photograph(projection * canvasMatrix * Matrix4::CreateTranslationMatrix(Size2(100.0f, 100.0f)));
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