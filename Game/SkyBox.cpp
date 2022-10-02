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

#include "BuffersRegistro.hpp"
#include "SkyBox.hpp"


SkyBox::SkyBox(string FileObj, string fileTexture0)
{

    shader.CreateShader("ShadersSkybox/shader.vert", "ShadersSkybox/shader.frag");

    string pathTextures = "Texturas/SkyBoxTextures/";
    pathTextures += fileTexture0;
    texture.LoadTexture(pathTextures);

    string pathModelos = "Modelos/";
    pathModelos += FileObj;

    ModelTemp modelo;
    loadOBJ(pathModelos.c_str(), modelo);
    modelIndexing(modelo, modeloIndexado);

    time.getElapsedTime();

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
void SkyBox::Render(Camera & camera)
{
    float deltaTime = 2.0 * time.getElapsedTime().asSeconds();
    glBindVertexArray(buffers.VertexArrayObject);

    shader.Use();

    texture.Use(Texture0);

    shader.SetTexture("mytexture", 0);
    
    mat4 model = mat4(1.0);
    model = translate(model, vec3(camera.position.x, camera.position.y + 50.0f, camera.position.z));
    model = rotate(model, radians(deltaTime), vec3(0.0, 1.0, 0.0));
    model = scale(model, vec3(250.0f));

    shader.SetMatrix4("model", model);
    shader.SetMatrix4("view", camera.ViewMatrix);
    shader.SetMatrix4("projection", camera.ProjectionMatrix);

    glDrawElements(GL_TRIANGLES, modeloIndexado.indices.size(), GL_UNSIGNED_SHORT, (void*)0);

}
void SkyBox::Delete()
{
    buffers.DeleteBuffers();
    texture.DeleteTextures();
    shader.DeleteProgramShader();
}