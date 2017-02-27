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
    
    #define PROPERTY(type, name) DEFINE_PROPERTY(type, name); DEFINE_PROPERTY_R(public, type, name); DEFINE_PROPERTY_W(public, type, name);
    #define PROPERTY_R(type, name) DEFINE_PROPERTY(type, name); DEFINE_PROPERTY_R(public, type, name);
    #define PROPERTY_W(type, name) DEFINE_PROPERTY(type, name); DEFINE_PROPERTY_W(public, type, name);
    

    #define V_PROPERTY(visibility, type, name) DEFINE_PROPERTY(type, name); DEFINE_PROPERTY_R(visibility, type, name); DEFINE_PROPERTY_W(visibility, type, name);
    #define V_PROPERTY_R(visibility, type, name) DEFINE_PROPERTY(type, name); DEFINE_PROPERTY_R(visibility, type, name);
    #define V_PROPERTY_W(visibility, type, name) DEFINE_PROPERTY(type, name); DEFINE_PROPERTY_W(visibility, type, name);
   

    #define DEFINE_PROPERTY(type, name) private:\
                    type m_##name;
    #define DEFINE_PROPERTY_R(visibility, type, name) visibility :\
                    inline type & name (void) { return m_##name; }\
                    inline type const & name (void) const { return m_##name; }
    #define DEFINE_PROPERTY_W(visibility, type, name) visibility :\
                    inline void name (const type & p_##name) { m_##name = p_##name; }

                
    class BaseObject
    {
    public:
        //持久
        void retain(void);
        //释放
        void release(void);

        //对象被引用次数
        PROPERTY_R(int, quoteCount);
    protected:
        BaseObject(void);
    private:
    };
}

#endif //__BASE_OBJECT_H__