#include <vector>
#include <stdio.h>
#include <cstring>
#include <iostream>
#include <string>
#include <map>
using namespace std;

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "ImageProgram.hpp"
#include "ShaderProgram.hpp"

#include "Texto.hpp"


void Texto::initText2D(string texturePath)
{
    string pathTextures = "Texturas/";
    pathTextures += texturePath;
    texture.LoadTexture(pathTextures);

    shader.CreateShader("ShadersTexto/shader.vert", "ShadersTexto/shader.frag");
}
// texto que vai ser apresentado, posicao x e y, tamanho
void Texto::printText2D(string text, vec3 color, int x, int y, int size)
{
    unsigned int length = strlen(text.c_str());

	// Fill buffers
	std::vector<glm::vec2> vertices;
	std::vector<glm::vec2> UVs;
	for ( unsigned int i=0 ; i<length ; i++ ){
		
		glm::vec2 vertex_up_left    = glm::vec2( x+i*size     , y+size );
		glm::vec2 vertex_up_right   = glm::vec2( x+i*size+size, y+size );
		glm::vec2 vertex_down_right = glm::vec2( x+i*size+size, y      );
		glm::vec2 vertex_down_left  = glm::vec2( x+i*size     , y      );

		vertices.push_back(vertex_up_left   );
		vertices.push_back(vertex_down_left );
		vertices.push_back(vertex_up_right  );

		vertices.push_back(vertex_down_right);
		vertices.push_back(vertex_up_right);
		vertices.push_back(vertex_down_left);

		char character = text[i];
		float uv_x = (character%16)/16.0f;
		float uv_y = (character/16)/16.0f;

		glm::vec2 uv_up_left    = glm::vec2( uv_x           , uv_y );
		glm::vec2 uv_up_right   = glm::vec2( uv_x+1.0f/16.0f, uv_y );
		glm::vec2 uv_down_right = glm::vec2( uv_x+1.0f/16.0f, (uv_y + 1.0f/16.0f) );
		glm::vec2 uv_down_left  = glm::vec2( uv_x           , (uv_y + 1.0f/16.0f) );
		UVs.push_back(uv_up_left   );
		UVs.push_back(uv_down_left );
		UVs.push_back(uv_up_right  );

		UVs.push_back(uv_down_right);
		UVs.push_back(uv_up_right);
		UVs.push_back(uv_down_left);
	}
	

	glGenVertexArrays(1, &VertexArrayObject);

	glBindVertexArray(VertexArrayObject);

	glGenBuffers(1, &Text2DVertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, Text2DVertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices[0], GL_STATIC_DRAW);
	
	GLuint AttributeLocationVerticesScreenspace = shader.GetAtributeLocation("vertexPosition_screenspace");
	glEnableVertexAttribArray(AttributeLocationVerticesScreenspace);
	glVertexAttribPointer(AttributeLocationVerticesScreenspace, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 );

	glGenBuffers(1, &Text2DUVBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, Text2DUVBufferID);
	glBufferData(GL_ARRAY_BUFFER, UVs.size() * sizeof(glm::vec2), &UVs[0], GL_STATIC_DRAW);

	GLuint AttributeLocationUvs = shader.GetAtributeLocation("vertexUV");
	glEnableVertexAttribArray(AttributeLocationUvs);
	glVertexAttribPointer(AttributeLocationUvs, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 );


	shader.Use();
    
    texture.Use(Texture0);
    shader.SetTexture("myTextureSampler", 0);

	glDrawArrays(GL_TRIANGLES, 0, 6);

}
void Texto::Delete()
{
	glDeleteBuffers(1, &Text2DVertexBufferID);
	glDeleteBuffers(1, &Text2DUVBufferID);

	glDeleteVertexArrays(1, &VertexArrayObject);

    shader.DeleteProgramShader();
    texture.DeleteTextures();
}
