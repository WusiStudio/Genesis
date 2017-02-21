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
        vertexsCount(8);
        indiesCount(17);
        return true;
    }

    const bool Cube::init(const Size3 & size)
    {
        m_size = size;
        Vec3 tempVertexs[8] = { Vec3(-m_size.width / 2, -m_size.height / 2, -m_size.depth / 2),
                                Vec3(m_size.width / 2, -m_size.height / 2, -m_size.depth / 2), 
                                Vec3(-m_size.width / 2, m_size.height / 2, -m_size.depth / 2),
                                Vec3(m_size.width / 2, m_size.height / 2, -m_size.depth / 2),
                                Vec3(-m_size.width / 2, m_size.height / 2, m_size.depth / 2),
                                Vec3(m_size.width / 2, m_size.height / 2, m_size.depth / 2),
                                Vec3(-m_size.width / 2, -m_size.height / 2, m_size.depth / 2),
                                Vec3(m_size.width / 2, -m_size.height / 2, m_size.depth / 2)
                                };
        vertexs(tempVertexs);

        unsigned short tempIndies[17] = {0, 1, 2, 3, 4, 5, 6, 7, 0xFFFF, 3, 5, 1, 7, 0, 6, 2, 4};
        indies(tempIndies);

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
            glDrawElements(GL_TRIANGLE_STRIP, 8, GL_UNSIGNED_SHORT, nullptr);
            glDrawElements(GL_TRIANGLE_STRIP, 8, GL_UNSIGNED_SHORT, (const void *)(9 * sizeof(GLushort)));
        }

        return true;
    }

}