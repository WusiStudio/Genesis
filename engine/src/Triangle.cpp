#include "Triangle.h"
#include "WSLog.h"
#include "Materia.h"
#include "Image.h"
#include "Textrue2D.h"

namespace engine
{
    using WsTools::Log;
    using engine::Image;
    using engine::Textrue2D;
    
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

        Vec3 tempVertexs[3] = {vertex_1, vertex_2, vertex_3};

        vertexs(tempVertexs);

        return bindVaoData();
    }

     const bool Triangle::tick(const float dp)
     {
         if(!Geometry::tick(dp)){ return false; }

         return true;
     }

     const bool Triangle::draw(const Matrix4 & eyeMatrix, const Matrix4 & screenMatrix) const
     {
        if(!Geometry::draw(eyeMatrix, screenMatrix)) return false;
        glDrawArrays(GL_TRIANGLES, 0, 3);
        return true;
     }
}