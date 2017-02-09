#version 330 core
layout( location = 1 ) in vec4 vColor;
out vec4 fColor;
void main()
{
    fColor = vColor;
}