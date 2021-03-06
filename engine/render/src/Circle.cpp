#include "Circle.h"
#include <cmath>
#include "WSLog.h"

namespace engine
{
    using WsTools::Log;

    Circle::Circle(void)
    {
        m_density = 0.5f;
    }

    Circle & Circle::Create(const float r)
    {
        Circle & result = Create();

        bool circleInit = result.init(r);

        assert(circleInit);

        if(!circleInit){ result.initializeError(1); }

        return result;
    }

    const bool Circle::init(void)
    {
        if(!Geometry::init()){ return false; }

        return true;
    }

    const bool Circle::init(const float r)
    {
        if(r <= 1.0f){ return false; }
        return radius(r);
    }

    const bool Circle::radius(const float r)
    {
        if(r <= 1.0f){ return false; }
        m_radius = r;

        float perimeter = 2 * PI * r;
        vertexsCount(perimeter * m_density + 1);
        indiesCount(vertexsCount() + 1);

        Vec3 tNormal(.0f, 1.0f, .0f);

        vertex(0, Vec3(0.0f));
        normal(0, tNormal);
        indie(0, 0);
        float intervalAngle = PI * 2 / (vertexsCount() - 1);

        for(int i = 0; i < vertexsCount() - 1; ++i)
        {
            vertex(i + 1, Vec3(m_radius * cos(intervalAngle * i), m_radius * sin(intervalAngle * i)));
            normal(i + 1, tNormal);
            indie(i + 1, i + 1);
        }

        Vec2 * tUvs = new Vec2[vertexsCount()];
        texCoords(tUvs);
        uvs(tUvs);
        delete[] tUvs;

        indie(vertexsCount(), 1);

        return bindVaoData();
    }

    const bool Circle::tick(const float dp)
     {
         if(!Geometry::tick(dp)) { return false; }

         return true;
     }


    const bool Circle::draw(const Matrix4 & eye_matrix, const Matrix4 & screen_matrix) const
     {
        if(!Geometry::draw(eye_matrix, screen_matrix)) return false;
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indiesBufferObject());
        glDrawElements(GL_TRIANGLE_FAN, indiesCount(), GL_UNSIGNED_SHORT, nullptr);
        return true;
     }

}