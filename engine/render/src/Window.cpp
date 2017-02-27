#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Window.h"
#include "WSLog.h"
#include "Gc.h"

#include "Vec.h"
#include "Rectangle.h"
#include "Materia.h"
#include "Color.h"

#include <algorithm>

namespace engine
{
    using WsTools::Log;

    vector<Window *> Window::ms_windowPool;
    const char * const Window::msc_nodeType = "Window";

    Window::Window(void)
    {
        m_window = nullptr;
        m_guiCamera = nullptr;
        m_guiCameraOutput = nullptr;

        m_worldCameraOutput = nullptr;
        m_onKeyPress = nullptr;
        m_onSizeChange = nullptr;
        m_onPositionChange = nullptr;

        m_show = false;
        m_fullScene = false;
    }

    Window::~Window(void)
    {         
        m_show = false;
        if(m_window)
        {
            glfwDestroyWindow(m_window);
        }

        auto it = std::find(ms_windowPool.begin(), ms_windowPool.end(), this);
        if(it != ms_windowPool.end())
        {
            ms_windowPool.erase(it);
        }
    }

    const vector<Window *> & Window::windowPool(void)
    {
        return ms_windowPool;
    }

    const char *  Window::nodeType(void) const
    {
        return msc_nodeType;
    }

    Node * Window::find(const string & id)
    {
        return (Node *)m_gui->find(id);
    }

    //添加子节点
    const bool Window::append(Node & child)
    {
        return m_gui->append(child);
    }
    //删除子节点
    const bool Window::remove(Node & child)
    {
        return m_gui->remove(child);
    }

    World & Window::gui(void) const
    {
        return (World &)*m_gui;
    }

    Window & Window::Create(const Size2 & size, const string & title)
    {
        Window & result = Create();
        bool windowInit = result.initWithInfo(size, title);

        assert(windowInit);

        if(!windowInit){ result.initializeError(-1); }

        return result;
    }

    const bool Window::init(void)
    {
        if(!Object::init()) { return false; }

        //window world
        m_gui = &World::Create();
        m_gui->retain();

        //创建主摄像机
        m_guiCamera = &Camera::Create();
        m_guiCamera->target(Vec3(.0f, .0f, .0f));
        m_guiCamera->position(Vec3(.0f, .0f, 1500.0f));
        m_guiCamera->cameraType(CameraType::Orthogonal);
        append(*m_guiCamera);

        m_guiCameraOutput = &CameraOutput::Create();
        BaseNode::append(*m_guiCameraOutput);
        m_guiCameraOutput->size(m_size);
        m_guiCameraOutput->camera(*m_guiCamera);

         m_worldCameraOutput = &CameraOutput::Create();
        // threeDWorldOutput.position(Vec3(.0f, .0f, 1200.0f));
        // threeDWorldOutput.size(m_size);
        append(*m_worldCameraOutput);

        ms_windowPool.push_back(this);

        return true;
    }

    const bool Window::initWithInfo(const Size2 & size, const string & title)
    {
        //设置参数
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
        //设置多重采样
        glfwWindowHint(GLFW_SAMPLES, 16);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

        //创建窗口
        m_size = Size2((float)(int)size.width, (float)(int)size.height);
        m_window = glfwCreateWindow((int)m_size.width, (int)m_size.height, title.c_str(), nullptr, nullptr);
        if (m_window == nullptr)
        {
            Log.error("Failed to create GLFW window ({0})", title);
            glfwTerminate();
            return false;
        }

        glfwMakeContextCurrent(m_window);
        gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

        // glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        //初始化窗口位置
        const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        m_position.x = (mode->width - m_size.width) / 2;
        m_position.y = (mode->height - m_size.height) / 2;
        position(m_position);

        //启用多重采样
        glEnable(GL_MULTISAMPLE);

        //判断多重采样是否启用成功
        if(glIsEnabled(GL_MULTISAMPLE))
        {
            GLint buffers ,samples;
            glGetIntegerv(GL_SAMPLE_BUFFERS,&buffers);
            glGetIntegerv(GL_SAMPLES,&samples);

            if(buffers > 0 && samples > 0)
            {
                Log.info("Enabled Multisample! buffers: {0}, samples: {1}", buffers, samples);
            }    
        }
        
        //启用深度测试
        glEnable(GL_DEPTH_TEST);
        if(glIsEnabled(GL_DEPTH_TEST))
        {
            Log.info("Enabled Depth Test!");
        }

        //启用图元重启
        glEnable(GL_PRIMITIVE_RESTART);
        glPrimitiveRestartIndex(0xFFFF);
        if(glIsEnabled(GL_PRIMITIVE_RESTART))
        {
            Log.info("Enabled Primitive Restart!");
        }
        
        // glfwSetErrorCallback(error_callback);

        //引擎按键处理
        static auto staticKeyCallBack = [](GLFWwindow * window, int key, int scancode, int action, int mode)->void
        {
            for(auto itemWindow : ms_windowPool)
            {
                if(itemWindow->m_window != window)
                {
                    continue;
                }

                if(!itemWindow->m_onKeyPress)
                {
                    break;
                }
                itemWindow->m_onKeyPress(key, scancode, action, mode);
            }
        };

        //引擎窗口size改变处理
        static auto staticWindowSizeCallBack = [](GLFWwindow* window, int width, int height)->void
        {
            for(auto itemWindow : ms_windowPool)
            {
                if(itemWindow->m_window != window)
                {
                    continue;
                }

                itemWindow->m_size = Size2((float)width, (float)height);
                itemWindow->m_guiCamera->viewPortSize(itemWindow->m_size);

                #if defined(__APPLE__) && defined(__MACH__)
                    //不重新指定区域也行 还没有弄明白为什么这样
                    glViewport(0, 0, width * 2, height * 2);
                #else
                    glViewport(0, 0, width, height);
                #endif

                // Log.info("window size : {0}", itemWindow->m_size);

                if(!itemWindow->m_onSizeChange)
                {
                    break;
                }
                
                itemWindow->m_onSizeChange(itemWindow->m_size);
            }
        };

        static auto staticWindowPosCallBack = [](GLFWwindow* window, int xpos, int ypos)->void
        {
            for(auto itemWindow : ms_windowPool)
            {
                if(itemWindow->m_window != window)
                {
                    continue;
                }

                itemWindow->m_position = Vec2((float)xpos, (float)ypos);
                // Log.info("window pos : {0}", itemWindow->m_position);

                if(!itemWindow->m_onPositionChange)
                {
                    break;
                }
                
                itemWindow->m_onPositionChange(itemWindow->m_position);
            }
        };

        //按键
        glfwSetKeyCallback(m_window, staticKeyCallBack);

        //窗口大小
        glfwSetWindowSizeCallback(m_window, staticWindowSizeCallBack);

        //窗口位置
        glfwSetWindowPosCallback(m_window, staticWindowPosCallBack);

        return true;
    }

    void Window::title(const string & title) const
    {
        glfwSetWindowTitle(m_window, title.c_str());
    }

    void Window::icon(const string & icon_path) const
    {
        // GLFWimage images[2];
        // images[0] = load_icon("my_icon.png");
        // images[1] = load_icon("my_icon_small.png");
        // glfwSetWindowIcon(m_window, 2, images);
    }

    void Window::size(const Size2 & size) const 
    {
        if(m_fullScene)
        {
            Log.warning("Is In Full Sreen Mode!");
            return;
        }
        glfwSetWindowSize(m_window, (int)size.width, (int)size.height);
    }

    void Window::sizeLimitSize(const Size2 & min, const Size2 & max) const
    {
        glfwSetWindowSizeLimits(m_window, (int)min.width, (int)min.height, (int)max.width, (int)max.height);
    }

    void Window::position(const Vec2 & p_position) const
    {
        glfwSetWindowPos(m_window, (int)p_position.x, (int)p_position.y);
    }

    void Window::fullScreen(void)
    {
        GLFWmonitor * monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode * mode = glfwGetVideoMode(monitor);
        glfwSetWindowMonitor(m_window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
        #if defined(__APPLE__) && defined(__MACH__)
            m_position = Vec2(.0f, .0f);
            if(m_onPositionChange) m_onPositionChange(m_position);
        #endif
        m_fullScene = true;
    }

    void Window::cancelFullScreen(const Size2 & size)
    {
        if(!m_fullScene)
        {
            return;
        }
        const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        cancelFullScreen(size, Vec2((mode->width - size.width) / 2, (mode->height - size.height) / 2));
    }

    void Window::cancelFullScreen(const Size2 & size, const Vec2 & p_position)
    {
        if(!m_fullScene)
        {
            return;
        }
        const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        glfwSetWindowMonitor(m_window, nullptr, (int)p_position.x, (int)p_position.y, (int)size.width, (int)size.height, mode->refreshRate);
        #if defined(__APPLE__) && defined(__MACH__)
            m_position = p_position;
            if(m_onPositionChange) m_onPositionChange(m_position);
        #endif
        m_fullScene = false;
    }

    void Window::onKeyPress(function<void(int key, int scancode, int action, int mode)> call_back)
    {
        m_onKeyPress = call_back;
    }
    void Window::onSizeChange(function<void(const Size2 & size)> call_back)
    {
        m_onSizeChange = call_back;
    }
    void Window::onPositionChange(function<void(const Vec2 & p_position)> call_back)
    {
        m_onPositionChange = call_back;
    }

    void Window::show(void)
    {
        if(m_show){
            return;
        }
        m_show = true;

        //
        glClearColor(0.0, 0.0, 0.0, 1.0);

        while(!glfwWindowShouldClose(m_window) && m_show)
        {
            //计算距上一帧时差
            static double prevDisplayTime = 0.0f;
            double currDisplayTime = glfwGetTime() * 1000;
            float dateSpace = (float)(currDisplayTime - prevDisplayTime);

            //glfw事件系统
            glfwPollEvents();

            //动画系统、计时器执行

            if(onTick()) onTick()(dateSpace);

            //确定所有元素的位置后计算所有元素的位置
            tick(dateSpace);

            //清空画布
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            //绘制画板
            draw(Matrix4(1.0f), Matrix4(1.0f));

            //垃圾回收
            Gc::Instance().clean();

            //渲染
            glfwSwapBuffers(m_window);

            prevDisplayTime = currDisplayTime;
        };
        glfwTerminate();
    }
}