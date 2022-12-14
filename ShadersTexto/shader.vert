#version 330 core

layout(location = 0) in vec2 vertexPosition_screenspace;
layout(location = 1) in vec2 vertexUV;

out vec2 UV;

// uniform vec2 scale;

void main(){

	// posicao na tela
	vec2 vertexPosition_homoneneousspace = vertexPosition_screenspace - vec2(400,300); // ponto ancora 400, 300 

	// scala 
	vertexPosition_homoneneousspace /= vec2(200, 300);
	gl_Position =  vec4(vertexPosition_homoneneousspace,-1, 1); // -1, 1
	
	UV = vertexUV;
}
// #version 330 core

// // Input vertex data, different for all executions of this shader.
// layout(location = 0) in vec2 vertexPosition_screenspace;
// layout(location = 1) in vec2 vertexUV;

// // Output data ; will be interpolated for each fragment.
// out vec2 UV;

// uniform vec2 scale;

// void main(){

// 	// Output position of the vertex, in clip space
// 	// map [0..800][0..600] to [-1..1][-1..1]
// 	vec2 vertexPosition_homoneneousspace = vertexPosition_screenspace - vec2(400,300); // [0..800][0..600] -> [-400..400][-300..300]
// 	// vertexPosition_homoneneousspace /= vec2(200, 300);
// 	vec2 thisScale = vec2(scale.x - 200, scale.y);
// 	vertexPosition_homoneneousspace /= thisScale;
// 	gl_Position =  vec4(vertexPosition_homoneneousspace,0,1);
	
// 	// UV of the vertex. No special space for this one.
// 	UV = vertexUV;
// }