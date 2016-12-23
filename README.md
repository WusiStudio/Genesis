# Genesis engine

## 编译
> cmake ( gcc | clang | vistual c++ )

## 依赖
>- glfw库
>- 显卡支持 opengl3.3 

## 平台
> osx linux win10

## 命名规范

>|类型                             |命名规范           |介绍                                                   |
>|:------------------------------ |:---------------- |:---------------------------------------------------- |
>|macro                           |--                |全部大些,下划线间隔                                      |
>|class, struct, static method    |pascal            |每个单词首字母大写                                       |
>|method                          |camel             |第一个单词外的首字母大些                                  |
>|attribute                       |匈牙利+camel       |属性_对象描述(全局变量 g_, 常量 c_, 成员变量 m_, 静态变量 s_)|
>|parameter                       |--                |全部小写, 下划线间隔                                     |
