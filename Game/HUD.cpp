#include <vector>
#include <stdio.h>
#include <cstring>
#include <iostream>
#include <string>
#include <map>
using namespace std;

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
using namespace sf;

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
using namespace glm;

#include "../common/ImageProgram.hpp"
#include "../common/ShaderProgram.hpp"
#include "../common/Camera.hpp"

#include "BuffersRegistro.hpp"

#include "HUD.hpp"

Hud::Hud(string texturePath)
{
    string pathTextures = "Texturas/";
    pathTextures += texturePath;
    
    texture.LoadTexture(pathTextures);

    shader.CreateShader("ShadersHUD/shader.vert", "ShadersHUD/shader.frag");


	std::vector<glm::vec2> vertices;
	std::vector<glm::vec2> UVs;

	time.getElapsedTime().asMicroseconds();

	// 						 X		y
	vertices.push_back(vec2( -0.5f, -0.5f )); // down left
	vertices.push_back(vec2( -0.5f,  0.5f )); 	// up left
	vertices.push_back(vec2(  0.5f,  0.5f ));	// up right
	vertices.push_back(vec2(  0.5f, -0.5f ));		// down right
	vertices.push_back(vec2( -0.5f, -0.5f ));		// down left
	vertices.push_back(vec2(  0.5f,  0.5f ));	// up right


	UVs.push_back(vec2(0.0f, 1.0f));
	UVs.push_back(vec2(0.0f, 0.0f));
	UVs.push_back(vec2(1.0f, 0.0f));
	UVs.push_back(vec2(1.0f, 1.0f));
	UVs.push_back(vec2(0.0f, 1.0f));
	UVs.push_back(vec2(1.0f, 0.0f));


	buffers.InitBuffers();

	glBindVertexArray(buffers.VertexArrayObject);

	glBindBuffer(GL_ARRAY_BUFFER, buffers.Text2DVertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices[0], GL_STATIC_DRAW);
	
	GLuint AttributeLocationVerticesScreenspace = shader.GetAtributeLocation("vertexPosition_screenspace");
	glEnableVertexAttribArray(AttributeLocationVerticesScreenspace);
	glVertexAttribPointer(AttributeLocationVerticesScreenspace, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 );

	glBindBuffer(GL_ARRAY_BUFFER, buffers.Text2DUVBufferID);
	glBufferData(GL_ARRAY_BUFFER, UVs.size() * sizeof(glm::vec2), &UVs[0], GL_STATIC_DRAW);

	GLuint AttributeLocationUvs = shader.GetAtributeLocation("vertexUV");
	glEnableVertexAttribArray(AttributeLocationUvs);
	glVertexAttribPointer(AttributeLocationUvs, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 );

}
// Os valores das posicoes estão entre o valor de -2500 e 2500
// em coordenadas de dispositivos noramalizadas com as posicoes
// 0 representando os centro
// Os valores da scala podem ser definidos em valores menores que 20
// valores maior que 20 , ficam fora da display
void Hud::Render(Camera & camera)
{
	float deltaTime = time.getElapsedTime().asSeconds();
	glBindVertexArray(buffers.VertexArrayObject);
	
	shader.Use();
    
    texture.Use(Texture0);
	
	model = mat4(1.0);

	shader.SetMatrix4("model", model);
	// shader.SetVec2("position", position);
	// shader.SetVec2("scala", scala);


    shader.SetTexture("myTextureSampler", 0);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	cout << deltaTime << endl;

}
void Hud::Delete()
{
    buffers.DeleteBuffer();

    shader.DeleteProgramShader();
    texture.DeleteTextures();
}
