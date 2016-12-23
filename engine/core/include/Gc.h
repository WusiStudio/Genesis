#pragma once
#ifndef __GC_H__
#define __GC_H__

#include <list>
#include <iostream>
#include "BaseObject.h"
#include "Object.h"
using namespace std;

namespace engine
{    
    class Gc : protected BaseObject
    {
    public:
        //获取实例
        static Gc & Instance(void);

        //销毁没有被引用的对象
        void clean(void);
        
        //加入管理对象池
        const bool watch(Object &);

    protected:
        Gc(void);
        ~Gc(void);

        //销毁所有管理对象
        void cleanAll(void);
    private:
        //对象池
        list<BaseObject *> * m_objectPool;
    };
}
#endif //__GC_H__
