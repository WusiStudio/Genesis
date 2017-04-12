#include "Fps.h"
#include "Chartlet.h"
#include "Color.h"
#include <sstream>

using std::stringstream;

namespace engine
{
    //显示60个fps数据
    int Fps::sm_drawFpsCount = 60;
    //每300毫秒统计一次fps
    float Fps::sm_StatisticalInterval = 300.0f;

    Fps::Fps(void)
    {
        m_dataOffset = 0;
        m_label = nullptr;

        m_cacheSumFps = .0f;
        m_cacheFpsCount = 0;
        m_cacheTime = .0f;
    }

    const bool Fps::init(void)
    {
        if(!Geometry::init()) { return false; }

         m_size = Size2(70.0f, 40.0f);

        float widthHalf = m_size.width / 2;
        float heightHalf = m_size.height / 2;

        float unitWidth = m_size.width / (sm_drawFpsCount - 1);
        float fpsBaseLinePosY = m_size.height / 3 * 2 - heightHalf;

        Chartlet & Chartlet = Chartlet::Create();
        if(Chartlet.fault()){ return false; }

        Label & label = Label::Create();
        if(label.fault()){ return false; }
        label.position(Vec2(-widthHalf, heightHalf));
        append(label);
        m_label = &label;

        ColorRGBA * colors = new ColorRGBA[(unsigned int)(sm_drawFpsCount * 2 + 6)];
        vertexsCount((unsigned short)(sm_drawFpsCount * 2 + 6));

        ColorRGBA contentColor(.2f, .8f, .0f, .4f);
        ColorRGBA borderColor(1.0f, .0f, .0f, 1.0f);
        ColorRGBA baseLineColor(.9f, .8f, .0f, .9f);

        Vec3 tNormal(.0f, 1.0f, .0f);
        for(size_t i = 0; i < vertexsCount(); ++i)
        {
            normal((unsigned short)i, tNormal);
        }
        
        //
        for(size_t i = 0; i < (size_t)sm_drawFpsCount; ++i)
        {
            float x = -widthHalf + unitWidth * i;
            vertex((unsigned short)(i * 2), Vec3(x, -heightHalf));
            vertex((unsigned short)(i * 2 + 1), Vec3(x, -heightHalf));

            colors[i * 2] = contentColor;
            colors[i * 2 + 1] = contentColor;

            m_fpsList.push_back(0.0f);
        }

        //边框线
        vertex((unsigned short)(sm_drawFpsCount * 2 + 0), Vec3(-widthHalf, -heightHalf));
        vertex((unsigned short)(sm_drawFpsCount * 2 + 1), Vec3(widthHalf, -heightHalf));
        vertex((unsigned short)(sm_drawFpsCount * 2 + 2), Vec3(widthHalf, heightHalf));
        vertex((unsigned short)(sm_drawFpsCount * 2 + 3), Vec3(-widthHalf, heightHalf));

        colors[sm_drawFpsCount * 2 + 0] = borderColor;
        colors[sm_drawFpsCount * 2 + 1] = borderColor;
        colors[sm_drawFpsCount * 2 + 2] = borderColor;
        colors[sm_drawFpsCount * 2 + 3] = borderColor;

        //
        
        vertex((unsigned short)(sm_drawFpsCount * 2 + 4), Vec3(-widthHalf, fpsBaseLinePosY));
        vertex((unsigned short)(sm_drawFpsCount * 2 + 5), Vec3(widthHalf, fpsBaseLinePosY));

        colors[sm_drawFpsCount * 2 + 4] = baseLineColor;
        colors[sm_drawFpsCount * 2 + 5] = baseLineColor;

        Chartlet.colors(colors, vertexsCount());
        delete[] colors;
        return bindChartlet(Chartlet);
    }

    const bool Fps::bindChartlet(Chartlet & c)
    {
        return Geometry::bindChartlet(c);
    }

    const bool Fps::tick(const float dp)
    {
        if(!Geometry::tick(dp)) return false;

        float fps = 1000.0f / dp;

        m_cacheSumFps += fps;
        m_cacheTime += dp;
        ++m_cacheFpsCount;

        if(m_cacheSumFps < sm_StatisticalInterval)
        {
            return true;
        }

        fps = m_cacheSumFps / m_cacheFpsCount;
        m_cacheSumFps = .0f;
        m_cacheFpsCount = 0;
        m_cacheSumFps = .0f;

        stringstream strs;
        strs << fps;

        string sfps = strs.str();
        auto dotIndex = sfps.find('.');
        if((int)dotIndex != -1 && sfps.length() - dotIndex > 2)
        {
            sfps = sfps.substr(0, dotIndex + 3);
        }

        if(m_label)
        {
            m_label->text("FPS: " + sfps);
        }
        
        if((int)m_fpsList.size() >= sm_drawFpsCount)
        {
            m_fpsList[(unsigned int)m_dataOffset] = fps;
            m_dataOffset = (m_dataOffset + 1) % sm_drawFpsCount;
        }else{
            m_fpsList.push_back(fps);
        }

        float widthHalf = m_size.width / 2;
        float heightHalf = m_size.height / 2;

        float unitWidth = m_size.width / (sm_drawFpsCount - 1);
        //更新VAO
        for(short i = 0; i < sm_drawFpsCount; ++i)
        {
            short fpsIndex = (short)((m_dataOffset + i) % sm_drawFpsCount);
            if(fpsIndex >= (short)m_fpsList.size()) break;
            float postY = m_size.height / 3 * 2 * m_fpsList[(unsigned int)fpsIndex] / 60.0f - heightHalf;
            vertex((unsigned short)(i * 2), Vec3(-widthHalf + unitWidth * i, postY > heightHalf ? heightHalf : postY));
        }

        return bindVaoData();
    }

    const bool Fps::draw(const Matrix4 & eye_matrix, const Matrix4 & screen_matrix) const
    {
        if(!Geometry::draw(eye_matrix, screen_matrix)) return false;
        glDrawArrays(GL_TRIANGLE_STRIP, 0, sm_drawFpsCount * 2);
        glDrawArrays(GL_LINE_LOOP, sm_drawFpsCount * 2, 4);
        glDrawArrays(GL_LINES, sm_drawFpsCount * 2 + 4, 2);
        
        return true;
    }

    Fps::~Fps(void)
    {
        if(m_label) { m_label->release(); }
    }
}