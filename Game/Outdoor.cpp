#include "iostream"
#include "string"
using namespace std;

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
using namespace sf;

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/norm.hpp>

using namespace glm;

#include "../common/ShaderProgram.hpp"
#include "../common/ImageProgram.hpp"
#include "../common/Camera.hpp"

#include "Outdoor.hpp"

Outdoor::Outdoor(string fileTexture)
{
    shader.CreateShader("ShadersOutdoor/shader.vert", "ShadersOutdoor/shader.frag");
    
    string pathTextures = "Texturas/";
    pathTextures += fileTexture;
    texture.LoadTexture(pathTextures);


    static const GLfloat g_vertex_buffer_data[] = 
    { 
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
	};

    glGenVertexArrays(1, &VertexArrayObject);
    glBindVertexArray(VertexArrayObject);

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_DYNAMIC_DRAW);

    GLuint AttributeLocationVertices = shader.GetAtributeLocation("squareVertices");
    glEnableVertexAttribArray(AttributeLocationVertices);
    glVertexAttribPointer(AttributeLocationVertices, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
}
void Outdoor::Render(Camera & camera)
{
    glBindVertexArray(VertexArrayObject);

    shader.Use();

    texture.Use(Texture0);

    shader.SetTexture("myTextureSampler", 0);

    shader.SetVec3("CameraRight_worldspace", camera.right );
    shader.SetVec3("CameraUp_worldspace",    camera.up );

    shader.SetVec3("BillboardPos", position);
    shader.SetVec2("BillboardSize", vec2(6.0f, 0.625f));
    
    shader.SetFloat("LifeLevel", LifeLevel);

    shader.SetMatrix4("view", camera.ViewMatrix);
    shader.SetMatrix4("projection", camera.ProjectionMatrix);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void Outdoor::Update()
{
    if(Keyboard::isKeyPressed(Keyboard::Up) && LifeLevel <= 0.958991) LifeLevel += 0.01;
    if(Keyboard::isKeyPressed(Keyboard::Down) && LifeLevel >= 0) LifeLevel -= 0.01;
}
void Outdoor::Delete()
{
    texture.DeleteTextures();

    glDeleteBuffers(1, &vertexbuffer);
    glDeleteVertexArrays(1, &VertexArrayObject);

    shader.DeleteProgramShader();
}