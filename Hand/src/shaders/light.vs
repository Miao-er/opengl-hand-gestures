#version 450
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 texCoords;
uniform mat4 mvp;
out vec2 texcoord;
void main()
{
    gl_Position = mvp * vec4(aPos, 1.0);
    texcoord = texCoords;
}