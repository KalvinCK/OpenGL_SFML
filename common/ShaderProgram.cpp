#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <stdexcept>
#include <map>
using namespace std;

#include <GL/glew.h>

#include <glm/glm.hpp>
using namespace glm;

#include "ShaderProgram.hpp"


// classe shader
void ShaderProgram::CreateShader(string vertexShaderFile, string fragmentShaderFile)
{
    // Vertex Shader
    GLuint vertexBuffer = glCreateShader(GL_VERTEX_SHADER);
    string vertexProgram;

    ifstream vertexShaderStream(vertexShaderFile, ios::in);
    if(vertexShaderStream.is_open())
    {
        stringstream sstr;
        sstr << vertexShaderStream.rdbuf();
        vertexProgram = sstr.str();
        vertexShaderStream.close();
    } else 
    {
        cout << "Nao foi possivel abrir vertex Shader : " << vertexShaderFile << endl;
    }

    // Fragment Shader
    GLuint fragmentBuffer = glCreateShader(GL_FRAGMENT_SHADER);
    string fragmentProgram;

	ifstream FragmentShaderStream(fragmentShaderFile, ios::in);
	if(FragmentShaderStream.is_open()){

		stringstream sstr;
		sstr << FragmentShaderStream.rdbuf();
		fragmentProgram = sstr.str();
		FragmentShaderStream.close();
	} else 
    {
        cout << "Nao foi possivel abrir o FragmentShader: " << fragmentShaderFile << endl;
    }

    GLint Result = GL_FALSE;
    int InfoLogLength;

    // compilando o vertex shader
    char const * VertexSourcePointer = vertexProgram.c_str();
    glShaderSource(vertexBuffer, 1, &VertexSourcePointer, NULL);
    glCompileShader(vertexBuffer);

    // checando se houve erros
    glGetShaderiv(vertexBuffer, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(vertexBuffer, GL_INFO_LOG_LENGTH, &InfoLogLength);
    
	if ( InfoLogLength > 0 ){
		vector<char> VertexShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(vertexBuffer, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        cout << "Erro ao Compilar o shader: " << &VertexShaderErrorMessage[0] << endl;
        exit(EXIT_FAILURE);
	}


    // Compilando fragment shader
	char const * FragmentSourcePointer = fragmentProgram.c_str();
	glShaderSource(fragmentBuffer, 1, &FragmentSourcePointer , NULL);
	glCompileShader(fragmentBuffer);

    // Chacando se houve erros
    glGetShaderiv(fragmentBuffer, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(fragmentBuffer, GL_INFO_LOG_LENGTH, &InfoLogLength);

	if ( InfoLogLength > 0 ){
		vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(fragmentBuffer, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
        cout << "Erro ao Compilar o shader: " << &FragmentShaderErrorMessage[0] << endl;
        exit(EXIT_FAILURE);
	}

    // Linkando o programa | Criando o programa shader
	Handle = glCreateProgram();
	glAttachShader(Handle, vertexBuffer);
	glAttachShader(Handle, fragmentBuffer);
	glLinkProgram(Handle);

	// checando o programa
	glGetProgramiv(Handle, GL_LINK_STATUS, &Result);
	glGetProgramiv(Handle, GL_INFO_LOG_LENGTH, &InfoLogLength);

	if ( InfoLogLength > 0 ){
		vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(Handle, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        cout << "Shader Error... " << &ProgramErrorMessage[0] << endl;
	}
	
	glDetachShader(Handle, vertexBuffer);
	glDetachShader(Handle, fragmentBuffer);
	
	glDeleteShader(vertexBuffer);
	glDeleteShader(fragmentBuffer);

    GLint LenghtUniformIndices;
    glGetProgramiv(Handle, GL_ACTIVE_UNIFORMS, &LenghtUniformIndices);

    for(int i = 0; i < LenghtUniformIndices; i++)
    {
        GLint tamanho;
        GLenum type;
        GLchar nameUniform[70];

        glGetActiveUniform( Handle, i, 50, NULL, &tamanho, &type, &nameUniform[0]);

        GLuint location = glGetUniformLocation(Handle, nameUniform);

        uniformLocations.insert(pair<string, GLuint>(nameUniform, location));
    }

}
void ShaderProgram::checkingUniform(const char * name)
{
    try
    {
        if(!uniformLocations.count(name)) 
            throw invalid_argument("Error. ");
    }
    catch(const exception & erro)
    {
        cerr << erro.what() << "O uniform: " << name << " nao foi encontrado!" << endl;
        exit(1);
    }
}
void ShaderProgram::Use()
{
    glUseProgram(Handle);
}
int ShaderProgram::GetAtributeLocation(const char * name)
{
    return glGetAttribLocation(Handle, name);
}
// define a unidade da textura no shader
void ShaderProgram::SetTexture(const char * name, int data)
{
    checkingUniform(name);
    glUniform1i(uniformLocations[name], (GLuint)data);
}
// define um float
void ShaderProgram::SetFloat(const char * name, float data)
{
    checkingUniform(name);
    glUniform1f(uniformLocations[name], (GLfloat)data);
}
// define um vec2
void ShaderProgram::SetVec2(const char * name, vec2 data)
{
    checkingUniform(name);
    glUniform2f(uniformLocations[name], data.x, data.y);
}
// define um vec3
void ShaderProgram::SetVec3(const char * name, vec3 data)
{
    checkingUniform(name);
    glUniform3f(uniformLocations[name], data.x, data.y, data.z);
}
// define um vec4
void ShaderProgram::SetVec4(const char * name, vec4 data)
{
    checkingUniform(name);
    glUniform4f(uniformLocations[name], data.x, data.y, data.z, data.w);
}
// define uma matrix 3x3
void ShaderProgram::SetMatrix3(const char * name, mat3 data)
{
    checkingUniform(name);
    glUniformMatrix4fv(uniformLocations[name], 1 , GL_FALSE, &data[0][0]);
}
// define uma matrix 4x4
void ShaderProgram::SetMatrix4(const char * name, mat4 data)
{
    checkingUniform(name);
    glUniformMatrix4fv(uniformLocations[name], 1 , GL_FALSE, &data[0][0]);
}

// apos o termino do programa deevemos chamar está funcao para apagar o Programa de shader
void ShaderProgram::DeleteProgramShader()
{
    glDeleteProgram(Handle);
}