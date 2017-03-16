#include "Rectangle.h"


namespace engine
{
    Rectangle & Rectangle::Create(const Size2 & size)
    {
        Rectangle & result = Create();

        bool rectangleInit = result.initWithSize(size);

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

    const bool Rectangle::initWithSize(const Size2 & size)
    {
        m_size = size;
        float widthHalf = m_size.width / 2;
        float heightHalf = m_size.height / 2;

        Vec3 tempVertexs[4] = { Vec3(-widthHalf, -heightHalf), Vec3(widthHalf, -heightHalf), Vec3(widthHalf, heightHalf), Vec3(-widthHalf, heightHalf) };
        Vec3 tempNormals[4] = { Vec3(.0f, 1.0f, .0f), Vec3(.0f, 1.0f, .0f), Vec3(.0f, 1.0f, .0f), Vec3(.0f, 1.0f, .0f) };
        vertexs(tempVertexs);
        normals(tempNormals);

        unsigned short tempIndies[4] = {0, 1, 3, 2};
        indies(tempIndies);

        return bindVaoData();
    }

     const bool Rectangle::draw(const Matrix4 & eye_matrix, const Matrix4 & screen_matrix) const
     {
        if(!Geometry::draw(eye_matrix, screen_matrix)) return false;
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indiesBufferObject());
        glDrawElements(GL_TRIANGLE_STRIP, indiesCount(), GL_UNSIGNED_SHORT, nullptr);
        return true;
     }

}