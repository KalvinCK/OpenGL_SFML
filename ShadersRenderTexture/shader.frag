#version 460 core

in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D renderedTexture;
uniform float time;

void main()
{
	FragColor = texture( renderedTexture, TexCoord + 0.005 * vec2( sin(time + 1024.0 * TexCoord.x),cos(time + 768.0 * TexCoord.y)) );
}