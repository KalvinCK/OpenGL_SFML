#version 330 core

layout(location = 0) in vec2 vertexPosition_screenspace;
layout(location = 1) in vec2 vertexUV;

out vec2 UV;

uniform mat4 model;

void main(){

	// // posicao na tela
	// vec2 vertexPosition_homoneneousspace = vertexPosition_screenspace - vec2(50, 50); // 300, 300 center
	// vec2 pos = position / vec2(50, 50);
	// vertexPosition_homoneneousspace += pos;


	// // scala aumentar o valor abaixa a escala
	// vec2 num_scala = vec2(1000, 1000) / scala;
	// vertexPosition_homoneneousspace /= num_scala; // 400
	gl_Position = model * vec4(vertexPosition_screenspace, -1, 1); // -1, 1
	UV = vertexUV;
}
// #version 330 core

// layout(location = 0) in vec2 vertexPosition_screenspace;
// layout(location = 1) in vec2 vertexUV;

// out vec2 UV;

// uniform vec2 position; // 2500
// uniform vec2 scala; // 0

// void main(){

// 	// posicao na tela
// 	vec2 vertexPosition_homoneneousspace = vertexPosition_screenspace - vec2(50, 50); // 300, 300 center
// 	vec2 pos = position / vec2(50, 50);
// 	vertexPosition_homoneneousspace += pos;


// 	// scala aumentar o valor abaixa a escala
// 	vec2 num_scala = vec2(1000, 1000) / scala;
// 	vertexPosition_homoneneousspace /= num_scala; // 400
// 	gl_Position =  vec4(vertexPosition_homoneneousspace,-1, 1); // -1, 1
// 	UV = vertexUV;
// }
