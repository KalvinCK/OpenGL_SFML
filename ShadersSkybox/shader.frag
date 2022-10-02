#version 330 core

in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D mytexture;

void main(){
	FragColor = texture(mytexture, TexCoord);
	// float gamma = 0.3;
    // FragColor.rgb = pow(FragColor.rgb, vec3(1.0/gamma));
}