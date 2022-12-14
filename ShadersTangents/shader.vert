#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoords;
layout(location = 2) in vec3 aNormals;
layout(location = 3) in vec3 aTangentes;
layout(location = 4) in vec3 aBitangentes;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 TexCoords;

void main(){

	TexCoords = aTexCoords;   
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}

