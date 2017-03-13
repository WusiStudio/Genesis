#version 330 core
layout( location = 2 ) in vec2 vTexCoord;

out vec2 fTexCoord;

void main()
{
    fTexCoord = vTexCoord;
}