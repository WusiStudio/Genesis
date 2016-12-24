#include "TestAppaction.h"

#include "Circle.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Node.h"
#include "WSLog.h"
#include "Image.h"
#include "Textrue2D.h"
#include "Matrix.h"

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
        window().append(Triangle::Create(Vec2(.0f, .0f), Vec2(400.0f, .0f), Vec2(.0f, 300.0f)));

        // Triangle & haha = Triangle::Create(Vec2(.0f, .0f), Vec2(400.0f, .0f), Vec2(.0f, 300.0f));

        engine::Rectangle & rectangle = Rectangle::Create(50.0f);
        rectangle.position(Vec2(500.0f, 500.0f));
        window().append(rectangle);

		Circle & fristCircle = Circle::Create(200.0f);
        fristCircle.position(Vec2(window().windowSize().width * 0.5f, window().windowSize().height * 0.5f));
        window().append(fristCircle);

		// ScreenWorld::Instance().append(fristCircle);

        // Vec3 location(1.0f, 2.0f, 3.0f);
        // Log.info("location[0] = {0}", location[0]);
        // Log.info("location[1] = {0}", location[1]);
        // Log.info("location[2] = {0}", location[2]);

        // location[1] += 5;

        // Log.info("location = {0}", location);

        Matrix2 matrix(Vec2(1.6666f, 3.152454f), Vec2(2.154f, 4.556f));

        Matrix2 matrix2(matrix);

        matrix[0][0] += 2.356645f;

        Log.info("matrix[0][0] = {0}", matrix[0][0]);
        Log.info("matrix[1][1] = {0}", matrix[1][0]);

        

        Log.info("matrix2[0][0] = {0}", matrix2[0][0]);
        Log.info("matrix2[1][1] = {0}", matrix2[1][0]);

        Log.info("matrix2 = {0}", matrix2);

        Matrix3 matrix3(5.123456789f);
        Log.info("matrix3 = {0}", matrix3);



        // Textrue2D::Create("asds.jpg");
 }

 void TestAppaction::update(const float dt)
 {
        // Log.info("update: {0, F4}", dt);
        // int currDisplayTime = Zeus::Instance().runningTime();

		// Node & tr = *ScreenWorld::Instance().root().chidren().at(1);
		// tr.position(Vec2((Zeus::Instance().windowSize().width - 100) * 0.5f + cos(currDisplayTime / 1000.0f) * (Zeus::Instance().windowSize().width - 100) * 0.5f, (Zeus::Instance().windowSize().height - 100) * 0.5f + sin(currDisplayTime / 1000.0f) * (Zeus::Instance().windowSize().height - 100) * 0.5f));
 }