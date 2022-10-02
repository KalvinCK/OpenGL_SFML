#version 330 core

in vec2 TexCoords;

out vec4 FragColor;

uniform sampler2D myTextureSampler;

void main(){
	FragColor = texture( myTextureSampler, TexCoords );
	FragColor.a = 0.4;
}