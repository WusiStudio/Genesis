#pragma once
#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <vector>

#include "Vec.h"
#include "BaseNode.h"
#include "Node.h"
#include "Camera.h"
#include "CameraOutput.h"

namespace engine
{
    using namespace std;

    class Window : public BaseNode
    {
    public:
        static const vector<Window *> & windowPool(void);
        static Window & Create(const Size2 & size, const string & title);

        //类型
        const char *  nodeType(void) const override final;

        //添加子节点
        const bool append(Node & child);
        //删除子节点
        const bool remove(Node & child);

        void setWindowTitle(const string & title) const;
        void setWindowIcon(const string & iconPath) const;
        void setWindowSize(const Size2 & size) const;
        void setWindowSizeLimitSize(const Size2 & min, const Size2 & max) const;
        void setWindowPosition(const Vec2 & position) const;

        Size2 windowSize(void) const;
        Vec2 windowPosition(void) const;

        void onKeyPress(function<void(int key, int scancode, int action, int mode)> callBack);
        void onSizeChange(function<void(const Size2 & size)> callBack);
        void onPositionChange(function<void(const Vec2 & position)> callBack);

        void show(void);

    protected:
        virtual ~Window(void);
        CREATEFUNC(Window);

        const bool init(void) override;
        virtual const bool initWithInfo(const Size2 & size, const string & title);

    private:
        Window(void);

        static const char * const ms_nodeType;

        //用于多窗口事件回调
        static vector<Window *> ms_windowPool;

        Size2 m_windowSize;
        Vec2 m_windowPoaition;

        // CameraOutput * m_canvas;
        // Camera * m_mainCamera;

        GLFWwindow * m_window;
        function<void(int key, int scancode, int action, int mode)> m_onKeyPress;
        function<void(const Size2 & size)> m_onSizeChange;
        function<void(const Vec2 & position)> m_onPositionChange;

        bool m_show = false;

    };
}

#endif //__WINDOW_H__