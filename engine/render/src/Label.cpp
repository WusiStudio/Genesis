#include "Label.h"

#include "Tool.h"

namespace engine
{
    using tools::sTOWs;

    Label::Label(void)
    {
        m_refresh = true;
        m_characterBox = nullptr;
        m_color = ColorRGB(.0f);
        m_align = Align::left;
        m_italic = false;
        m_underline = Underline::normal;
        m_font = nullptr;
        m_fontSize = 16;
        m_chartlet = nullptr;

        m_text = "";
    }

    Label::~Label(void)
    {
        if(m_characterBox) { m_characterBox->release(); }
        if(m_font)  { m_font->release(); }
        if(m_chartlet) m_chartlet->release();
    }

    const bool Label::init(void)
    {
        if(!Node::init()){ return false; }

        m_characterBox = &Node::Create();
        if(m_characterBox->fault()){ return false; }
        append(*m_characterBox);

        m_font = &Font::defaultFont();
        m_font->retain();

        return true;
    }

    void Label::text(const string & p_text)
    {
        if(p_text == m_text) return;

        m_text = p_text;
        m_refresh = true;
    }

    void Label::forceRefresh(void)
    {
        m_refresh = true;
    }

    const bool Label::bindChartlet(Chartlet & m)
    {
        if(m_chartlet)
        {
            m_chartlet->release();
        }
        m_chartlet = &m;
        m_chartlet->retain();
        m_characterBox->each([this](BaseNode & node) -> bool{
            Character * character = dynamic_cast<Character *>(&node);
            if(!character) return true;

            character->bindChartlet(*m_chartlet);
            return true;
        });

        return true;
    }

    void Label::font(Font & p_font)
    {
        if(m_font)
        {
            m_font->release();
        }
        m_font = &p_font;
        m_font->retain();
    }

    Font & Label::font(void) const
    {
        return *m_font;
    }

    const bool Label::tick(const float dt)
    {
        if(m_refresh)
        {
            //渲染文字变化，重新排列文字
            if(!m_characterBox->clear()){ Log.error("Label Clear Fault!"); }
            m_characterBoxSize = Size2(.0f, (float)m_fontSize * 3 / 2);

            wstring wstr = sTOWs(m_text);
            for(size_t i = 0; i < wstr.size(); ++i)
            {

                CharacterInfo & characterInfo = m_font->loadCharacterInfo(wstr.at(i), m_fontSize);
                if(m_characterCache.size() <= i)
                {
                    Character & character = Character::Create(characterInfo);

                    if(m_chartlet) { character.bindChartlet(*m_chartlet); }
                    character.retain();
                    m_characterCache.push_back(&character);
                }else{
                    m_characterCache[i]->characterInfo(characterInfo);
                }

                (*m_characterCache[i]).position(Vec2(m_characterBoxSize.width, .0f));

                m_characterBoxSize.width += characterInfo.advance();
                m_characterBox->append(*m_characterCache[i]);

            }

            m_refresh = false;
        }
        
        return Node::tick(dt);
    }
}