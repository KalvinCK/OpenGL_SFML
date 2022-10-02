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

#include "RenderSprite.hpp"

RenderSprite::RenderSprite(string fileTexture)
{
    shader.CreateShader("ShadersSprite/shader.vert", "ShadersSprite/shader.frag");
    
    string pathTextures = "Texturas/";
    pathTextures += fileTexture;
    texture.LoadTexture(pathTextures);

    time.getElapsedTime().asMicroseconds();

    static const GLfloat v_quad[] = 
    { 
        0.0f, -1.0f, 0.0f,
        0.0f,  0.0f, 0.0f,
        1.0f,  0.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        1.0f,  0.0f, 0.0f,
        1.0f, -1.0f, 0.0f
	};

    static const GLfloat uv_quad[] =
    {
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 1.0f,
        1.0f, 0.0f
    };

    glGenVertexArrays(1, &VertexArrayObject);
    glBindVertexArray(VertexArrayObject);

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(v_quad), v_quad, GL_DYNAMIC_DRAW);

    GLuint AttributeLocationVertices = shader.GetAtributeLocation("squareVertices");
    glEnableVertexAttribArray(AttributeLocationVertices);
    glVertexAttribPointer(AttributeLocationVertices, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glGenBuffers(1, &uvsbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvsbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uv_quad), uv_quad, GL_DYNAMIC_DRAW);

    GLuint AtributeLocationUvs = shader.GetAtributeLocation("squareUvs");
    glEnableVertexAttribArray(AtributeLocationUvs);
    glVertexAttribPointer(AtributeLocationUvs, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

}
void RenderSprite::Render(Camera & camera)
{
    float deltaTime = time.getElapsedTime().asSeconds();
    glBindVertexArray(VertexArrayObject);

    shader.Use();
    texture.Use(Texture0);

    mat4 model = mat4(1.0);
    shader.SetMatrix4("model", model);
    shader.SetMatrix4("view", camera.ViewMatrix);
    shader.SetMatrix4("projection", camera.ProjectionMatrix);


    shader.SetTexture("myTextureSampler", 0);

    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void RenderSprite::Update()
{
    
}
void RenderSprite::Delete()
{
    texture.DeleteTextures();

    glDeleteBuffers(1, &vertexbuffer);
    glDeleteBuffers(1, &uvsbuffer);
    glDeleteVertexArrays(1, &VertexArrayObject);

    shader.DeleteProgramShader();
}