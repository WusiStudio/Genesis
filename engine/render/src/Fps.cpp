#include "Fps.h"
#include "Materia.h"
#include "Color.h"
#include <sstream>

using std::stringstream;

namespace engine
{
    int Fps::sm_drawFpsCount = 60;


    Fps::Fps(void)
    {
        m_dataOffset = 0;
    }

    const bool Fps::init(void)
    {
        if(!Geometry::init()) { return false; }

         m_size = Size2(120.0f, 80.0f);

        float widthHalf = m_size.width / 2;
        float heightHalf = m_size.height / 2;

        float unitWidth = m_size.width / (sm_drawFpsCount - 1);
        float fpsBaseLinePosY = m_size.height / 3 * 2 - heightHalf;

        Materia & materia = Materia::Create();
        if(materia.fault()){ return false; }

        Label & label = Label::Create();
        if(label.fault()){ return false; }
        label.position(Vec2(-widthHalf, heightHalf));
        append(label);
        m_label = &label;

        ColorRGBA * colors = new ColorRGBA[sm_drawFpsCount * 2 + 6];
        vertexsCount(sm_drawFpsCount * 2 + 6);

        ColorRGBA contentColor(.2f, .8f, .0f, .8f);
        ColorRGBA borderColor(1.0f, .0f, .0f, 1.0f);
        ColorRGBA baseLineColor(.8f, .8f, .2f, 1.0f);
        //
        for(short i = 0; i < sm_drawFpsCount; ++i)
        {
            float x = -widthHalf + unitWidth * i;
            vertex(i * 2, Vec3(x, -heightHalf));
            vertex(i * 2 + 1, Vec3(x, -heightHalf));

            colors[i * 2] = contentColor;
            colors[i * 2 + 1] = contentColor;

            m_fpsList.push_back(0.0f);
        }

        //边框线
        vertex(sm_drawFpsCount * 2 + 0, Vec3(-widthHalf, -heightHalf));
        vertex(sm_drawFpsCount * 2 + 1, Vec3(widthHalf, -heightHalf));
        vertex(sm_drawFpsCount * 2 + 2, Vec3(widthHalf, heightHalf));
        vertex(sm_drawFpsCount * 2 + 3, Vec3(-widthHalf, heightHalf));

        colors[sm_drawFpsCount * 2 + 0] = borderColor;
        colors[sm_drawFpsCount * 2 + 1] = borderColor;
        colors[sm_drawFpsCount * 2 + 2] = borderColor;
        colors[sm_drawFpsCount * 2 + 3] = borderColor;

        //
        
        vertex(sm_drawFpsCount * 2 + 4, Vec3(-widthHalf, fpsBaseLinePosY));
        vertex(sm_drawFpsCount * 2 + 5, Vec3(widthHalf, fpsBaseLinePosY));

        colors[sm_drawFpsCount * 2 + 4] = baseLineColor;
        colors[sm_drawFpsCount * 2 + 5] = baseLineColor;

        materia.colors(colors, vertexsCount());
        delete[] colors;
        return bindMateria(materia);
    }

    const bool Fps::bindMateria(Materia & m)
    {
        return Geometry::bindMateria(m);
    }

    const bool Fps::tick(const float dp)
    {
        if(!Geometry::tick(dp)) return false;

        float fps = 1000.0f / dp;

        stringstream strs;
        strs << fps;

        string sfps = strs.str();
        auto dotIndex = sfps.find('.');
        if(dotIndex != -1)
        {
            sfps = sfps.substr(0, dotIndex + 2);
        }

        // m_label->text("FPS: " + sfps);

        if(m_fpsList.size() >= sm_drawFpsCount)
        {
            m_fpsList[m_dataOffset] = fps;
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
            short fpsIndex = (m_dataOffset + i) % sm_drawFpsCount;
            if(fpsIndex >= m_fpsList.size()) break;
            float postY = m_size.height / 3 * 2 * m_fpsList[fpsIndex] / 60.0f - heightHalf;
            vertex(i * 2, Vec3(-widthHalf + unitWidth * i, postY > heightHalf ? heightHalf : postY));
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
}