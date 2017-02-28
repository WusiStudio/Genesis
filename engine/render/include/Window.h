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
#include "World.h"

namespace engine
{
    using std::string;
    using std::vector;
    
    class Window : public BaseNode
    {
        PROPERTY_R(Size2, size);
        PROPERTY_R(Vec2, position);
    public:
        static const vector<Window *> & windowPool(void);
        static Window & Create(const Size2 & size, const string & title);

        //类型
        virtual const char *  nodeType(void) const override final;

        //查找指定id的子元素
        Node * find(const string & id);

        //添加子节点
        const bool append(Node & child);
        //删除子节点
        const bool remove(Node & child);

        World & gui(void) const;
        const bool bindCamera(Camera & camera);

        void title(const string & title) const;
        void icon(const string & icon_path) const;
        void size(const Size2 & size) const;
        void sizeLimitSize(const Size2 & min, const Size2 & max) const;
        void position(const Vec2 & p_position) const;

        void fullScreen(void);
        void cancelFullScreen(const Size2 & size);
        void cancelFullScreen(const Size2 & size, const Vec2 & p_position);

        void onKeyPress(function<void(int key, int scancode, int action, int mode)> call_back);
        void onSizeChange(function<void(const Size2 & size)> call_back);
        void onPositionChange(function<void(const Vec2 & position)> call_back);

        void show(void);
    protected:
        virtual ~Window(void);
        CREATEFUNC(Window);

        virtual const bool init(void) override;
        virtual const bool initWithInfo(const Size2 & size, const string & title);

    private:
        Window(void);

        static const char * const msc_nodeType;

        //用于多窗口事件回调
        static vector<Window *> ms_windowPool;

        //
        World * m_gui;
        Camera * m_guiCamera;
        CameraOutput * m_guiCameraOutput;

        CameraOutput * m_worldCameraOutput;

        GLFWwindow * m_window;
        
        //-------   Event  -------//
        //widnow event
        function<void(const Size2 & size)> m_onSizeChange;
        function<void(const Vec2 & position)> m_onPositionChange;
        //keyboard
        function<void(int key, int scancode, int action, int mode)> m_onKeyPress;
        //mouse
        function<void(double xpos, double ypos)> m_onMouseMove;
        function<void(double xoffset, double yoffset)> m_onMouseScroll;

        //window state
        bool m_show;
        bool m_fullScene;

    };
}

#endif //__WINDOW_H__