#version 430 core
layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 texcoord;

out vec2 texcoords;
uniform mat4 model;
void main(){
    gl_Position = model * vec4(pos, 1.0);
    texcoords = texcoord;
}