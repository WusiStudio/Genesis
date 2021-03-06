#pragma once
#ifndef __BASE_NODE_H__
#define __BASE_NODE_H__

#include "Object.h"
#include "Matrix.h"

#include <list>
#include <functional>
#include <string>
#include <map>

namespace engine
{
    using std::list;
    using std::function;
    using std::string;
    using std::map;

    class BaseNode : public Object
    {
        //父元素
        PROPERTY_R(BaseNode *, parent);
        PROPERTY_W(function<void(const float)>, onTick);
    public:
        virtual const char * nodeType(void) const = 0;

        void id(const string & id);
        string id(void) const;

        BaseNode & root(void) const;

        //从父元素删除自己
        const bool remove(void);

        //清空子元素
        const bool clear(void);

        //根据id查找子元素
        BaseNode * find(const string & id);
        
        //遍历子元素
        void each(function<bool(BaseNode & node)> cb) const;

    protected:
        BaseNode(void);
        virtual ~BaseNode(void);

        virtual const bool init(void) override;

        //添加子元素
        const bool append(BaseNode & child);
        //删除子元素
        const bool remove(BaseNode & child);

        function<void(const float)> onTick(void) const;
        virtual const bool tick(const float dt);
        virtual const bool draw(const Matrix4 & eye_matrix, const Matrix4 & screen_matrix) const;
        //
    private:
        string * m_id;
        list<BaseNode *> m_chidren;
        static map<string, BaseNode *> ms_catalogById;
    };
}

#endif //__BASE_NODE_H__