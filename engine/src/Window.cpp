#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Window.h"
#include "WSLog.h"
#include "Gc.h"

namespace engine
{
    using WsTools::Log;

    vector<Window *> Window::ms_windowPool;
    const char * const Window::msc_nodeType = "Window";

    const vector<Window *> & Window::windowPool(void)
    {
        return ms_windowPool;
    }

    const char *  Window::nodeType(void) const
    {
        return msc_nodeType;
    }

    //添加子节点
    const bool Window::append(Node & child)
    {
        return BaseNode::append(child);
    }
    //删除子节点
    const bool Window::remove(Node & child)
    {
        return BaseNode::remove(child);
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

        //创建主摄像机
        // m_mainCamera = & Camera::Create();

        // //创建摄像机画布
        // m_canvas = & CameraOutput::Create();
        // m_canvas->camera(* m_mainCamera);
        // // append(*m_canvas);
        // m_canvas->position(Vec2(50.0f));

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
        m_windowSize = Size2((float)(int)size.width, (float)(int)size.height);
        m_window = glfwCreateWindow((int)m_windowSize.width, (int)m_windowSize.height, title.c_str(), nullptr, nullptr);
        if (m_window == nullptr)
        {
            Log.error("Failed to create GLFW window ({0})", title);
            glfwTerminate();
            return false;
        }

        glfwMakeContextCurrent(m_window);
        gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);


        //启用多重采样 (未成功)
        if(glIsEnabled(GL_MULTISAMPLE))
        {
            GLint buffers ,samples;
            glGetIntegerv(GL_SAMPLE_BUFFERS,&buffers);
            glGetIntegerv(GL_SAMPLES,&samples);

            if(buffers > 0 && samples > 0)
                glEnable(GL_MULTISAMPLE);
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

                itemWindow->m_windowSize = Size2((float)width, (float)height);

                #if(!defined(APIENTRY))
                    glViewport(0, 0, width, height);
                #else
                    //不重新指定区域也行 还没有弄明白为什么这样
                    glViewport(0, 0, width * 2, height * 2);
                #endif

                Log.info("window size : {0}", itemWindow->m_windowSize);

                if(!itemWindow->m_onSizeChange)
                {
                    break;
                }
                
                itemWindow->m_onSizeChange(itemWindow->m_windowSize);
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

                if(!itemWindow->m_onPositionChange)
                {
                    break;
                }
                itemWindow->m_windowPoaition = Vec2((float)xpos, (float)ypos);
                itemWindow->m_onPositionChange(itemWindow->m_windowPoaition);
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

    void Window::setWindowTitle(const string & title) const
    {
        glfwSetWindowTitle(m_window, title.c_str());
    }

    void Window::setWindowIcon(const string & iconPath) const
    {
        // GLFWimage images[2];
        // images[0] = load_icon("my_icon.png");
        // images[1] = load_icon("my_icon_small.png");
        // glfwSetWindowIcon(m_window, 2, images);
    }

    void Window::setWindowSize(const Size2 & size) const 
    {
        glfwSetWindowSize(m_window, (int)size.width, (int)size.height);
    }

    void Window::setWindowSizeLimitSize(const Size2 & min, const Size2 & max) const
    {
        glfwSetWindowSizeLimits(m_window, (int)min.width, (int)min.height, (int)max.width, (int)max.height);
    }

    void Window::setWindowPosition(const Vec2 & position) const
    {
        glfwSetWindowPos(m_window, (int)position.x, (int)position.y);
    }

    Size2 Window::windowSize(void) const
    {
        return m_windowSize;
    }
    Vec2 Window::windowPosition(void) const
    {
        return m_windowPoaition;
    }

    void Window::onKeyPress(function<void(int key, int scancode, int action, int mode)> callBack)
    {
        m_onKeyPress = callBack;
    }
    void Window::onSizeChange(function<void(const Size2 & size)> callBack)
    {
        m_onSizeChange = callBack;
    }
    void Window::onPositionChange(function<void(const Vec2 & position)> callBack)
    {
        m_onPositionChange = callBack;
    }

    void Window::show(void)
    {
        if(m_show){
            return;
        }
        m_show = true;

        //
        glClearColor(0.0, 0.0, 0.0, 1.0);

        while(!glfwWindowShouldClose(m_window))
        {

            static double prevDisplayTime = 0.0f;
            double currDisplayTime = glfwGetTime() * 1000;
            float dateSpace = (float)(currDisplayTime - prevDisplayTime);

            glfwPollEvents();

            //动画系统、计时器执行

            if(onTick()) onTick()(dateSpace);

            // //确定所有元素的位置后计算所有元素的位置
            tick(dateSpace);

            // //清空画布
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // //以每个视口绘制
            draw(Matrix4::CreateProjectionMatrix(m_windowSize));

            //垃圾回收
            Gc::Instance().clean();

            //渲染
            glfwSwapBuffers(m_window);

            prevDisplayTime = currDisplayTime;
        };
        glfwTerminate();
    }

    Window::Window(void)
    {
        m_window = nullptr;
        m_onKeyPress = nullptr;
        m_onSizeChange = nullptr;
        m_onPositionChange = nullptr;
    }

    Window::~Window(void)
    {
        
    }
}