#version 330 core

layout( location = 1 ) in vec2 vFontTexCoord;

out vec2 fFontTexCoord;

void main()
{
    fFontTexCoord = vFontTexCoord;
}