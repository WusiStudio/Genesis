#pragma once
#ifndef __BASE_NODE_H__
#define __BASE_NODE_H__

#include "Object.h"
#include "Matrix.h"

#include <list>
#include <functional>
#include <string>

namespace engine
{
    using std::list;
    using std::function;
    using std::string;

    class BaseNode : public Object
    {
    public:
    
        virtual const char * nodeType(void) const = 0;

        void id(const string & id);
        string id(void) const;

        BaseNode & root(void);

        //父元素
        BaseNode * parent(void) const;

        //从父元素删除自己
        const bool remove(void);

        //清空子元素
        const bool clear(void);

        //根据id查找子元素
        BaseNode * find(const string & id);
        
        //遍历子元素
        void each(function<bool(BaseNode & node)> cb) const;

        void onTick(function<void(const float)> on_tick);

    protected:
        BaseNode(void);
        virtual ~BaseNode(void);

        const bool init(void) override;

        //添加子元素
        const bool append(BaseNode & child);
        //删除子元素
        const bool remove(BaseNode & child);

        function<void(const float)> onTick(void) const;
        virtual const bool tick(const float dt);
        virtual const bool draw(const Matrix4 & projection);
        //
    private:
        string * m_id;
        BaseNode * m_parent;
        list<BaseNode *> m_chidren;
        function<void(const float)> m_onTick;
    };
}

#endif //__BASE_NODE_H__