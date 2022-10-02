#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 squareVertices;
layout (location = 1) in vec2 squareUvs;

out vec2 TexCoords;

// uniform vec3 CameraRight_worldspace;
// uniform vec3 CameraUp_worldspace;
// uniform vec3 BillboardPos; // Position of the center of the billboard
// uniform vec2 BillboardSize; // Size of the billboard, in world units (probably meters)

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
	// vec3 particleCenter_wordspace = BillboardPos;
	
	// vec3 vertexPosition_worldspace = 
	// 	particleCenter_wordspace
	// 	+ CameraRight_worldspace * squareVertices.x * BillboardSize.x
	// 	+ CameraUp_worldspace * squareVertices.y * BillboardSize.y;


	// Output position of the vertex
	gl_Position = projection * view * model * vec4(squareVertices, 1.0);

	TexCoords = squareUvs;
}