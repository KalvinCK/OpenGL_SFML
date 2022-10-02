#version 330 core

in vec2 UV;

out vec4 FragColor;

uniform vec3 color;

uniform sampler2D myTextureSampler;

void main(){

	FragColor = texture( myTextureSampler, UV );
	// FragColor.rgb = color;
	
}