#pragma once
#ifndef __BASE_OBJECT_H__
#define __BASE_OBJECT_H__


// 所有的类都由此父类派生 （功能类除外）

//-------------------     standard     -------------------
//      类型            命名规范                介绍
// class, struct    pascal              每个单词首字母大写
// method           camel               第一个单词外的首字母大些
// attribute        匈牙利+camel         属性_对象描述(全局变量 g_, 常量 c_, 成员变量 m_, 静态变量 s_)

namespace engine
{
    class BaseObject
    {
    public:
        //持久
        void retain(void);
        //释放
        void release(void);

        int quoteCount(void);
    protected:
        BaseObject(void);
    private:
        //对象被引用次数
        int m_quoteCount;
    };
}

#endif //__BASE_OBJECT_H__