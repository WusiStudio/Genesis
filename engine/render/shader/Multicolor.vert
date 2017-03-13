#version 330 core
layout( location = 3 ) in vec4 vColor;
out vec4 fColor;
void main()
{
    fColor = vColor;
}