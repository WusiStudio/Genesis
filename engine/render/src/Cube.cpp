#include "Cube.h"


namespace engine
{
    Cube & Cube::Create(const Size3 & size)
    {
        Cube & result = Create();

        bool cubeInit = result.init(size);

        assert(cubeInit);

        if(!cubeInit){ result.initializeError(1); }

        return result;
    }

    const bool Cube::init(void)
    {
        if(!Geometry::init()){ return false; }
        vertexsCount(24);
        indiesCount(29);
        return true;
    }

    const bool Cube::init(const Size3 & size)
    {
        m_size = size;

        float widthHalf = m_size.width / 2;
        float heightHalf = m_size.height / 2;
        float depthHalf =  m_size.depth / 2;

        Vec3 tVertexs[24] = {
            
            Vec3(-widthHalf, heightHalf,depthHalf),
            Vec3(widthHalf, heightHalf,depthHalf),
            Vec3(-widthHalf, -heightHalf,depthHalf),
            Vec3(widthHalf, -heightHalf,depthHalf), 

            Vec3(-widthHalf, -heightHalf, -depthHalf),
            Vec3(widthHalf, -heightHalf, -depthHalf), 
            Vec3(-widthHalf, heightHalf, -depthHalf),
            Vec3(widthHalf, heightHalf, -depthHalf),

            Vec3(-widthHalf, heightHalf, -depthHalf),
            Vec3(-widthHalf, heightHalf,depthHalf),
            Vec3(-widthHalf, -heightHalf, -depthHalf),
            Vec3(-widthHalf, -heightHalf,depthHalf),
            
            Vec3(widthHalf, heightHalf,depthHalf),
            Vec3(widthHalf, heightHalf, -depthHalf),
            Vec3(widthHalf, -heightHalf,depthHalf), 
            Vec3(widthHalf, -heightHalf, -depthHalf), 

            Vec3(-widthHalf, heightHalf, -depthHalf),
            Vec3(widthHalf, heightHalf, -depthHalf),
            Vec3(-widthHalf, heightHalf, depthHalf),
            Vec3(widthHalf, heightHalf, depthHalf),

            Vec3(-widthHalf, -heightHalf, depthHalf),
            Vec3(widthHalf, -heightHalf, depthHalf), 
            Vec3(-widthHalf, -heightHalf, -depthHalf),
            Vec3(widthHalf, -heightHalf, -depthHalf)
        };

        Vec3 tNormals[24] = {
            Vec3(.0f, .0f, 1.0f),
            Vec3(.0f, .0f, 1.0f),
            Vec3(.0f, .0f, 1.0f),
            Vec3(.0f, .0f, 1.0f),

            Vec3(.0f, .0f, -1.0f),
            Vec3(.0f, .0f, -1.0f),
            Vec3(.0f, .0f, -1.0f),
            Vec3(.0f, .0f, -1.0f),

            Vec3(-1.0f, .0f, .0f),
            Vec3(-1.0f, .0f, .0f),
            Vec3(-1.0f, .0f, .0f),
            Vec3(-1.0f, .0f, .0f),

            Vec3(1.0f, .0f, .0f),
            Vec3(1.0f, .0f, .0f),
            Vec3(1.0f, .0f, .0f),
            Vec3(1.0f, .0f, .0f),

            Vec3(.0f, 1.0f, .0f),
            Vec3(.0f, 1.0f, .0f),
            Vec3(.0f, 1.0f, .0f),
            Vec3(.0f, 1.0f, .0f),

            Vec3(.0f, -1.0f, .0f),
            Vec3(.0f, -1.0f, .0f),
            Vec3(.0f, -1.0f, .0f),
            Vec3(.0f, -1.0f, .0f)
        };

        Vec2 tUvs[24] = {
            Vec2(.0f, 1.0f), Vec2(1.0f, 1.0f), Vec2(.0f, .0f), Vec2(1.0f, .0f),
            Vec2(.0f, 1.0f), Vec2(1.0f, 1.0f), Vec2(.0f, .0f), Vec2(1.0f, .0f),
            Vec2(.0f, 1.0f), Vec2(1.0f, 1.0f), Vec2(.0f, .0f), Vec2(1.0f, .0f),
            Vec2(.0f, 1.0f), Vec2(1.0f, 1.0f), Vec2(.0f, .0f), Vec2(1.0f, .0f),
            Vec2(.0f, 1.0f), Vec2(1.0f, 1.0f), Vec2(.0f, .0f), Vec2(1.0f, .0f),
            Vec2(.0f, 1.0f), Vec2(1.0f, 1.0f), Vec2(.0f, .0f), Vec2(1.0f, .0f)
        };

        vertexs(tVertexs, tNormals, tUvs);

        unsigned short tIndies[29] = {0, 1, 2, 3, 0xFFFF, 4, 5, 6, 7, 0xFFFF, 8, 9, 10, 11, 0xFFFF, 12, 13, 14, 15, 0xFFFF, 16, 17, 18, 19, 0xFFFF, 20, 21, 22, 23};
        indies(tIndies);

        return bindVaoData();
    }

    const bool Cube::draw(const Matrix4 & eye_matrix, const Matrix4 & screen_matrix) const
    {
        if(!Geometry::draw(eye_matrix, screen_matrix)) return false;

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indiesBufferObject());
        if(glIsEnabled(GL_PRIMITIVE_RESTART))
        {
            glDrawElements(GL_TRIANGLE_STRIP, indiesCount(), GL_UNSIGNED_SHORT, nullptr);
        }
        else
        {
            glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, nullptr);
            glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, (const void *)(5 * sizeof(GLushort)));
            glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, (const void *)(10 * sizeof(GLushort)));
            glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, (const void *)(15 * sizeof(GLushort)));
            glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, (const void *)(20 * sizeof(GLushort)));
            glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, (const void *)(25 * sizeof(GLushort)));
        }

        return true;
    }

}