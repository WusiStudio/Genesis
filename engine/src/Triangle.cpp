#include "Triangle.h"
#include "WSLog.h"
#include "Materia.h"

namespace engine
{
    using WsTools::Log;
    
    Triangle & Triangle::Create(const Vec3 & vertex_1, const Vec3 & vertex_2, const Vec3 & vertex_3)
    {
        Triangle & result = Create();
        
        bool triangleInit = result.init(vertex_1, vertex_2, vertex_3);

        assert(triangleInit);

        if(!triangleInit){ result.initializeError(1); }
        return result;
    }

    const bool Triangle::init(void)
    {
        if(!Geometry::init()){ return false; }

        vertexsCount(3);
        return true;
    }

    const bool Triangle::init(const Vec3 & vertex_1, const Vec3 & vertex_2, const Vec3 & vertex_3)
    {

        Materia & materia = Materia::Create();

        // ColorRGBA tempColors[3] = {ColorRGBA(.2f, 1.0f, .4f, 1.0f), ColorRGBA(.2f, 1.0f, .4f, 1.0f), ColorRGBA(.2f, 1.0f, .4f, 1.0f)};
        // materia.colors(tempColors, sizeof(tempColors) / sizeof(ColorRGBA));
        ColorRGBA colors[] = {
            ColorRGBA(1.0f, 1.0f, 0.0f, 1.0f),
            ColorRGBA(0.0f, 1.0f, 1.0f, 1.0f),
            ColorRGBA(0.0f, 1.0f, 0.0f, 1.0f)
        };
        materia.colors(colors, sizeof(colors) / sizeof(ColorRGBA));

        bindMateria(materia);
        Vec3 tempVertexs[3] = {vertex_1, vertex_2, vertex_3};

        vertexs(tempVertexs);

        return bindVaoData();
    }

     const bool Triangle::tick(const float dp)
     {
         if(!Geometry::tick(dp)){ return false; }

         return true;
     }

     const bool Triangle::draw(const Matrix4 & projection) const
     {
        return deputeDraw(projection, [this](void)->bool{
            glDrawArrays(GL_TRIANGLES, 0, 3);
            return true;
        });
     }
}