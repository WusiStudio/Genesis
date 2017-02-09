#version 330 core

in vec2 fTexCoord;

uniform sampler2D ourTexture;

void main()
{
    color = texture(ourTexture, fTexCoord);
}