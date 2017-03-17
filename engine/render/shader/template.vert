#version

layout( location = 0 ) in vec3 vPosition;
layout( location = 1 ) in vec3 vNormal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 fNormal;
out vec3 fVertexPos;

#globalCode

void main()
{
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vPosition, 1.0f);
    fVertexPos = vec3(modelMatrix * vec4(vPosition, 1.0f));
    fNormal = vNormal;
#mainCode
}