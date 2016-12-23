#pragma once
#ifndef __APPACTION_H__
#define __APPACTION_H__

#include "Object.h"
#include "World.h"
#include "Window.h"
#include <functional>


namespace engine
{
    class Appaction : public Object
    {
    public: 
        const bool init(void) override;

        //运行程序
        void run(int argc, char ** argv);

        //获取程序路径
        static string AppactionPath(void);

        //获取屏幕
        Window & window(void);

    protected:

        //程序开始
        virtual void start(void) = 0;

        //每一帧
        virtual void update(const float dt) = 0;

        virtual ~Appaction(void);
    private:

        static string ms_appactionPath;

        Window * m_mainWindow;  
    };
}


#endif //__APPACTION_H__