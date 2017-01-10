#version

layout( location = 0 ) in vec4 vPosition;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

#globalCode

void main()
{
#mainCode
    gl_Position = vPosition * modelMatrix * viewMatrix * projectionMatrix;
}