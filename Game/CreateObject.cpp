#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
using namespace sf;

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>


using namespace glm;

#include "../common/ShaderProgram.hpp"
#include "../common/ImageProgram.hpp"
#include "../common/LoadModel.hpp"
#include "../common/Camera.hpp"

#include "Movement.hpp"
#include "BuffersRegistro.hpp"
#include "CreateObject.hpp"



// CreateObject::CreateObject(const char * FileObj, const char * fileTexture0, const char * fileTexture1)
CreateObject::CreateObject(const char * FileObj, string fileTexture0)
{

    shader.CreateShader("Shaders/shader.vert", "Shaders/shader.frag");

    string pathTextures = "Texturas/";
    pathTextures += fileTexture0;
    texture0.LoadTexture(pathTextures);



    char pathModelos[250];
    sprintf(pathModelos, "Modelos/%s", FileObj);

    ModelTemp modelo;
    loadOBJ(pathModelos, modelo);
    modelIndexing(modelo, modeloIndexado);
    cout << "Model Load..." << endl;
    cout << "Positions : " << modeloIndexado.indexed_vertices.size() << endl;
    cout << "Uvs       : " << modeloIndexado.indexed_uvs.size()      << endl;
    cout << "Normals   : " << modeloIndexado.indexed_normals.size()  << endl;
    cout << "indices   : " << modeloIndexado.indices.size()          << endl << endl;


    time.getElapsedTime();

    for(int i = i; i < sizeof(moves)/sizeof(moves[0]); i++)
    {
        moves[i].setValues(vec2(0.4, 2.0), vec2(0.005, 0.02));
    }

    buffers.CreateBuffers();

	glBindVertexArray(buffers.VertexArrayObject);

    glBindBuffer(GL_ARRAY_BUFFER, buffers.vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, modeloIndexado.indexed_vertices.size() * sizeof(vec3), &modeloIndexado.indexed_vertices[0], GL_STATIC_DRAW);

    GLuint AttributeLocationVertices = shader.GetAtributeLocation("aPos");
    glEnableVertexAttribArray(AttributeLocationVertices);
    glVertexAttribPointer(AttributeLocationVertices, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, buffers.uvbuffer);
    glBufferData(GL_ARRAY_BUFFER, modeloIndexado.indexed_uvs.size() * sizeof(vec2), &modeloIndexado.indexed_uvs[0], GL_STATIC_DRAW);

    GLuint AttributeLocationUvs = shader.GetAtributeLocation("aTexCoords");
    glEnableVertexAttribArray(AttributeLocationUvs);
    glVertexAttribPointer(AttributeLocationUvs, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, buffers.normalbuffer);
    glBufferData(GL_ARRAY_BUFFER, modeloIndexado.indexed_normals.size() * sizeof(vec3), &modeloIndexado.indexed_normals[0], GL_STATIC_DRAW);

    GLuint AttributelsLocationNormals = shader.GetAtributeLocation("aNormals");
    glEnableVertexAttribArray(AttributelsLocationNormals);
    glVertexAttribPointer(AttributelsLocationNormals, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers.elementbuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, modeloIndexado.indices.size() * sizeof(unsigned short), &modeloIndexado.indices[0] , GL_STATIC_DRAW);

}

void CreateObject::Render(Camera & camera) // desenhar
{
    
    glBindVertexArray(buffers.VertexArrayObject);

    shader.Use();

    texture0.Use(Texture0);
    shader.SetTexture("myTexture", 0);
    
    mat4 model = mat4(1.0f);
    // model = rotate(model, radians(180.0f), vec3(0.0, 1.0, 0.0));
    model = translate(model, position);

    shader.SetMatrix4("model", model);
    shader.SetMatrix4("view", camera.ViewMatrix);
    shader.SetMatrix4("projection", camera.ProjectionMatrix);

    glDrawElements(GL_TRIANGLES, modeloIndexado.indices.size(), GL_UNSIGNED_SHORT, (void*)0);

}
void CreateObject::Update()
{
    float deltaTime = 0.05 * time.getElapsedTime().asSeconds();

    if(Keyboard::isKeyPressed(Keyboard::Numpad2))  position.y -= deltaTime;
    if(Keyboard::isKeyPressed(Keyboard::Numpad8))  position.y += deltaTime;
    if(Keyboard::isKeyPressed(Keyboard::Numpad4))  position.x -= deltaTime;
    if(Keyboard::isKeyPressed(Keyboard::Numpad6))  position.x += deltaTime;
    if(Keyboard::isKeyPressed(Keyboard::Subtract)) position.z -= deltaTime;
    if(Keyboard::isKeyPressed(Keyboard::Add))      position.z += deltaTime;

    if(Keyboard::isKeyPressed(Keyboard::R)) position = vec3(0.0f); // reset position the object

    // cout << "X: " << position.x << endl;
    // cout << "Y: " << position.y << endl;
    // cout << "Z: " << position.z << endl;
}
void CreateObject::Delete() // destruir
{
    buffers.DeleteBuffers();

    texture0.DeleteTextures();

    shader.DeleteProgramShader();
}

// // eixos x
// if(Keyboard::isKeyPressed(Keyboard::Numpad2))  position.y -= moves[0].upMove();
// // else position.y -= moves[0].downMove(); 

// if(Keyboard::isKeyPressed(Keyboard::Numpad8))  position.y += moves[1].upMove();
// // else position.y += moves[1].downMove();
// // eixo y 
// if(Keyboard::isKeyPressed(Keyboard::Numpad4))  position.x -= moves[2].upMove();
// // else position.x -= moves[2].downMove();

// if(Keyboard::isKeyPressed(Keyboard::Numpad6))  position.x += moves[3].upMove();
// // else position.x += moves[3].downMove();
// // eixo z
// if(Keyboard::isKeyPressed(Keyboard::Subtract)) position.z -= moves[4].upMove();
// // else position.z -= moves[4].downMove();

// if(Keyboard::isKeyPressed(Keyboard::Add))      position.z += moves[5].upMove();
// // else position.z += moves[5].downMove();