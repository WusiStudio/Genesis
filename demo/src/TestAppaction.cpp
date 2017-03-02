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
#include "Tool.h"
#include "File.h"

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
        window().onSizeChange([this](const Size2 & window_size){
            onWindowSizeChange(window_size);
        });

        window().cancelFullScreen(Size2(1440.0f / 2.0f, 900.0f / 2));
        

        Node & node = Node::Create();
        node.position(Vec3(20.0f, window().size().height - 20.0f, .0f));

		Circle & fristCircle = Circle::Create(20.0f);
        fristCircle.id("haha");

        node.append(fristCircle);
        window().append(node);

        Materia & materia = Materia::Create();
        Image & _img = Image::Create("2.png");
        Textrue2D & textrue2D = Textrue2D::Create(_img);
        materia.chartlet2D(textrue2D);

        fristCircle.bindMateria(materia);


        //world
        World & gameWorld = World::Create();
        gameWorld.id("gameWorld");

        Camera & gameWorldCamera = Camera::Create();
        gameWorldCamera.position(Vec3(800.0f, .0f, .0f));
        gameWorldCamera.viewPortSize(window().size());
        gameWorldCamera.target(Vec3(.0f, .0f, .0f));
        gameWorld.append(gameWorldCamera);

        window().bindCamera(gameWorldCamera);


        // Materia & colorMateria = Materia::Create();
        // ColorRGBA colors[] = {
        //     ColorRGBA(1.0f, 0.0f, 0.0f, 1.0f),
        //     ColorRGBA(0.0f, 1.0f, 0.0f, 1.0f)
            
        // };
        // colorMateria.colors(colors, sizeof(colors) / sizeof(ColorRGBA));

        // rectangle.bindMateria(colorMateria);
        // triangle.bindMateria(colorMateria);

        Cube & cube = Cube::Create(Size3(300.0f));
        cube.id("cube");
        cube.scale(1.0f);
        cube.bindMateria(materia);
        gameWorld.append(cube);



        File & pictrue2 = File::Create(Appaction::AppactionPath() + "source/picture/2.png");
        Log.info("pictrue2.uuid() = {0}", pictrue2.uuid());

        File & pictrue3 = File::Create(Appaction::AppactionPath() + "source/picture/3.png");
        Log.info("pictrue3.uuid() = {0}", pictrue3.uuid());


        // Log.info("我: {0}", (int)L'我');


        // string str("我没问题啊，可以输出字符啊");
        // Log.info("str.length: {0}, {1}", str.length(), str);
        // wstring wstr = /*L"我没问题啊，可以输出字符啊";*/ tools::sTOWs(str);
        // Log.info("wstr.length: {0}", wstr.length());

        // Log.info("sizeof(wchar_t) = {0}, sizeof(int) = {1}", sizeof(wchar_t), sizeof(int));
        // Log.info("wstr.find(L\"我\"): {0}", wstr.find(L"可以"));

        // std::wcout << wstr << endl;

        // for(int i = 0; i < wstr.length(); ++i)
        // {
        //     const wchar_t * wc = (const wchar_t *)wstr.c_str();
        //     cout << (int)*(wc + i) << endl;
        // }


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

 void TestAppaction::onWindowSizeChange(const Size2 & window_size)
 {
     Node * haha = (Node *)window().find("haha");
     if(haha)
     {
         ((Node *)haha->parent())->position(Vec3(20.0f, window_size.height - 20.0f, .0f));
     }
 }

 void TestAppaction::update(const float dt)
 {
        Node * haha = (Node *)window().find("haha");
        static float temp = .0f;
        Size2 windowSize = window().size();
        temp += dt;

        if(haha) 
        { 
            // haha->position(Vec3(windowSize.width / 2 + sin(temp / 500.0f) * 100.0f, windowSize.height / 2, 0.0f));
            haha->rotate(Vec3(.0f, sin(temp / 500.0f) * PI / 2, .0f));
        }

        World * gameWorld = World::getWorldById("gameWorld");
        if(gameWorld)
        {
            Cube * cube = (Cube *)(gameWorld->find("cube"));
            if(cube)
            {
                cube->rotate(cube->rotate() + Size3(PI / 180 / 2, 0, PI / 180 / 2));
            }
        }
 }