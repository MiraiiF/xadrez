#version 430 core
out vec4 cores;
out vec2 texcoords;

uniform sampler2D textura;
void main(){
    cores = texture(textura, texcoords);
}