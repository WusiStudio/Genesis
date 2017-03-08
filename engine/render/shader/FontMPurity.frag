#version 330 core

uniform vec4 fColor;
uniform sampler2D fontTexture;

in vec2 fFontTexCoord;

void main()
{
    color = fColor * vec4(1.0f, 1.0f, 1.0f, texture(fontTexture, fFontTexCoord).r);
}