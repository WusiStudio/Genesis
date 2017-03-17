#version

in vec3 fNormal;
out vec4 color;
uniform vec4 ambientStrength;
#globalCode

void main()
{
#mainCode
    color = vec4(color.xyz * ambientStrength.xyz * ambientStrength.w, color.w);
}

