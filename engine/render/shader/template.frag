#version

uniform vec4 ambientStrength;
uniform vec3 lightPos;

in vec3 fNormal;
in vec3 fVertexPos;
out vec4 color;

#globalCode

void main()
{
#mainCode

    vec3 ambient = vec3(ambientStrength) * ambientStrength.w;
    vec3 lightDir = normalize(lightPos - fVertexPos);
    vec3 diffuse =  max(dot(fNormal, lightDir), 0.0f) * vec3(1.0f, 1.0f, 1.0f);
    color = vec4((ambient + diffuse) * vec3(color.xyz), color.w);
}

