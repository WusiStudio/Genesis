#include "TestAppaction.h"

#include "Circle.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Node.h"
#include "WSLog.h"
#include "Image.h"
#include "Textrue2D.h"
#include "Matrix.h"
#include "Image.h"
#include "Cube.h"

#include "Uuid.h"

#include <iostream>

using WsTools::Log;

TestAppaction & TestAppaction::Instance(void)
{
    static TestAppaction & result = Create();
    assert(result.ready());
    return result;
}


 void TestAppaction::start(void)
 {
        window().fullScreen();
        window().cancelFullScreen(Size2(1440.0f / 2.0f, 900.0f / 2));
        // Triangle & triangle = Triangle::Create(Vec2(.0f, .0f), Vec2(400.0f, .0f), Vec2(.0f, 300.0f));
        // window().append(triangle);

        // engine::Rectangle & rectangle = Rectangle::Create(350.0f);
        // rectangle.position(Vec3(500.0f, 500.0f, 5.0f));
        // window().append(rectangle);

		// Circle & fristCircle = Circle::Create(200.0f);
        // fristCircle.id("haha");
        // fristCircle.position(Vec3(window().size().width * 0.5f, window().size().height * 0.5f, 10.0f));
        // window().append(fristCircle);

        Materia & materia = Materia::Create();
        Image & _img = Image::Create("2.png");
        Textrue2D & textrue2D = Textrue2D::Create(_img);
        materia.chartlet2D(textrue2D);

        // fristCircle.bindMateria(materia);


        Materia & colorMateria = Materia::Create();
        ColorRGBA colors[] = {
            ColorRGBA(1.0f, 0.0f, 0.0f, 1.0f),
            ColorRGBA(0.0f, 1.0f, 0.0f, 1.0f)
            
        };
        colorMateria.colors(colors, sizeof(colors) / sizeof(ColorRGBA));

        // rectangle.bindMateria(colorMateria);
        // triangle.bindMateria(colorMateria);

        Cube & cube = Cube::Create(Size3(300.0f));
        cube.id("cube");
        cube.scale(1.0f);
        cube.bindMateria(materia);
        window().append(cube);

        Log.info("我: {0}", (int)L'我');

        // Vec3 location(1.0f, 2.0f, 3.0f);
        // Log.info("location[0] = {0}", location[0]);
        // Log.info("location[1] = {0}", location[1]);
        // Log.info("location[2] = {0}", location[2]);

        // location[1] += 5;

        // Log.info("location = {0}", location);

        // Matrix2 matrix(Vec2(1.6666f, 3.152454f), Vec2(2.154f, 4.556f));

        // Matrix2 matrix2(matrix);

        // matrix[0][0] += 2.356645f;

        // Log.info("matrix[0][0] = {0}", matrix[0][0]);
        // Log.info("matrix[1][1] = {0}", matrix[1][0]);

        

        // Log.info("matrix2[0][0] = {0}", matrix2[0][0]);
        // Log.info("matrix2[1][1] = {0}", matrix2[1][0]);

        // Log.info("matrix2 = {0}", matrix2);

        // Matrix3 matrix3(5.123456789f);
        // Log.info("matrix3 = {0}", matrix3);


        // Image & img = Image::Create("2.png");
        // Log.info("image width: {0}, height: {1}", img.width(), img.height());

        // Textrue2D & textrue = Textrue2D::Create(img);
        // Log.info("textrue id: {0}", textrue.textrueId());

        // Matrix3 detTestMatrix3(
        //     Vec3(1.0f, .0f, 8.0f),
        //     Vec3(.0f, 1.0f, 5.0f),
        //     Vec3(.0f, 6.0f, 1.0f)
        // );
        // Log.info("{0}.det() = {1, F}", detTestMatrix3, detTestMatrix3.det());
        // Log.info("{0}.adjugate() = {1}", detTestMatrix3, detTestMatrix3.adjugate());
        // Log.info("{0}.inverse() = {1}", detTestMatrix3, detTestMatrix3.inverse());
        // Log.info("detTestMatrix3 * detTestMatrix3.inverse() = {0}", detTestMatrix3 * detTestMatrix3.inverse());

 }

 void TestAppaction::update(const float dt)
 {
        Node * haha = (Node *)window().find("haha");
        static float temp = .0f;
        Size2 windowSize = window().size();
        temp += dt;

        if(haha) 
        { 
            // haha->rotate(Vec3(0.0f, 0.0f, (haha->rotate().z > PI * 2 ? haha->rotate().z - PI * 2 : haha->rotate().z) + 0.01));
            // haha->scale(1.0f + sin(temp / 500.0f) * .1f);
            haha->position(Vec3(windowSize.width / 2 + sin(temp / 500.0f) * 100.0f, windowSize.height / 2, 0.0f));
            haha->rotate(Vec3(0.0f, 0.0f, sin(temp / 500.0f) * .2f));
        }

        Cube * cube = (Cube *)window().find("cube");

        if(cube)
        {
            cube->rotate(cube->rotate() + Size3(PI / 180 / 2, 0, PI / 180 / 2));
        }
 }