#include "Rectangle.h"


namespace engine
{
    Rectangle & Rectangle::Create(const Size2 & size)
    {
        Rectangle & result = Create();

        bool rectangleInit = result.init(size);

        assert(rectangleInit);

        if(!rectangleInit){ result.initializeError(1); }

        return result;
    }

    const bool Rectangle::init(void)
    {
        if(!Geometry::init()){ return false; }
        vertexsCount(4);
        indiesCount(4);
        return true;
    }

    const bool Rectangle::init(const Size2 & size)
    {
        m_size = size;
        Vec3 tempVertexs[4] = {Vec3(.0f, .0f), Vec3(m_size.width, .0f), Vec3(.0f, m_size.height), Vec3(m_size.width, m_size.height)};
        vertexs(tempVertexs);

        unsigned short tempIndies[4] = {0, 1, 2, 3};
        indies(tempIndies);

        return bindVaoData();
    }

    const bool Rectangle::tick(const float dp)
     {
         if(!Geometry::tick(dp)){ return false; }

         return true;
     }

     const bool Rectangle::draw(const Matrix4 & projection) const
     {
        if(!Geometry::draw(projection)) return false;
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indiesBufferObject());
        glDrawElements(GL_TRIANGLE_STRIP, indiesCount(), GL_UNSIGNED_SHORT, nullptr);
        return true;
     }

}