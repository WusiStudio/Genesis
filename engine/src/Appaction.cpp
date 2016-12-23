#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Appaction.h"
#include "Gc.h"
#include "File.h"
#include "Node.h"
#include "Vec.h"
#include "WSLog.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "World.h"
#include "CameraOutput.h"
#include "Window.h"

#include <regex>

namespace engine
{
    using std::smatch;
    using std::regex;
    using WsTools::Log;

    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
    {
        std::cout << key << std::endl;
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GL_TRUE);
    }

    void error_callback(int error, const char* description)
    {
        puts(description);
    }
    
    const bool Appaction::init(void)
    {
        if(!Object::init()) { return false; }
        retain();
        return true;
    }

    string Appaction::ms_appactionPath = "";

    void Appaction::run(int argc, char ** argv)
    {
        static bool running = false;
        if(running) return;
        running = true;

        
        static regex pathRegex("^([^/\\\\]*[/\\\\])+");
        smatch searchResult;
        string sourceAppactionPath = string(argv[0]);
        if(!regex_search(sourceAppactionPath, searchResult, pathRegex))
        {
            Log.info("Matching AppactionPath Error");
        }

        ms_appactionPath = string(searchResult[0]);

        //初始化glfw
        glfwInit();

        //创建manwindow
        m_mainWindow = &Window::Create(Size2(800, 600), "haha");
        m_mainWindow->retain();

        m_mainWindow->onKeyPress([](int key, int scancode, int action, int mode)->void{
            Log.info("press key: {0}", key);
        });

        m_mainWindow->onTick([this](const float dt)->void{
            update(dt);
        });
        
        start();

        //启动manwindow（阻塞线程）
        m_mainWindow->show();
    }

    string Appaction::AppactionPath(void)
    {
        return ms_appactionPath;
    }

    Window & Appaction::window(void)
    {
        return * m_mainWindow;
    }

    Appaction::~Appaction(void)
    {

    }

}
