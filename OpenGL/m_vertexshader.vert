#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;
varying vec4 col;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    col = vec4(aCol.x, aCol.y, aCol.z, 1.0);
};
