#pragma once
#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "BaseObject.h"

#include <cassert>

namespace engine
{
    #define CREATEFUNC(class) static class & Create(void)\
    {\
        Object * result = (Object *)new class();\
        bool initRes = result->init();\
        \
        assert(initRes);\
        \
        if(!initRes)\
        {\
            result->initializeError(1);\
        }\
        result->autoRelease();\
        return *(class *)result;\
    }

    class Object : public BaseObject
    {
    public:
        //获取可用状态
        const bool ready(void) const;
        //获取错误码 (0表示无错误)
        const int fault(void) const;

        //对象自动释放
        virtual const bool autoRelease(void);

        virtual const bool init(void);

        //初始化错误码
        PROPERTY_W(int, initializeError);
    protected:
        
        Object(void){}
        virtual ~Object(void){}

    private:
    };
}

#endif //__OBJECT_H__
