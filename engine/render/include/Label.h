#pragma once
#ifndef __LABEL_H__
#define __LABEL_H__

#include "Node.h"
#include "Color.h"
#include "Vec.h"
#include "Font.h"
#include "Chartlet.h"
#include "Character.h"

#include <vector>

using std::vector;
namespace engine
{
    class Label: public Node
    {
        enum Align
        {
            center = 0,
            left,
            right
        };
        enum Underline
        {
            normal = 0,
            solid,
            dashed,
            dotted,
        };
        PROPERTY(Align, align);
        PROPERTY(ColorRGB, color);
        PROPERTY(bool, italic);
        PROPERTY(Underline, underline);
        PROPERTY_R(string, text);
        PROPERTY(unsigned short, fontSize);
    public:
        CREATEFUNC(Label);
        void text(const string & p_text);
        void forceRefresh(void);

        const bool bindChartlet(Chartlet & c);
        
        void font(Font & p_font);
        Font & font(void) const;
    protected:
        Label(void);
        virtual const bool init(void) override;
        virtual ~Label(void);

        virtual const bool tick(const float dt) override;
    private:
        bool m_refresh;
        Size2 m_characterBoxSize;
        Node * m_characterBox;
        Font * m_font;
        Chartlet * m_chartlet;
        vector<Character *> m_characterCache;
    };
}

#endif //__LABEL_H__