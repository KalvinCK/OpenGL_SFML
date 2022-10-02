#include <GL/glew.h>

#include "BuffersRegistro.hpp"

void Buffers::CreateBuffers()
{
    glGenVertexArrays(1, &VertexArrayObject);

    glGenBuffers(1, &vertexbuffer);
    glGenBuffers(1, &uvbuffer);
    glGenBuffers(1, &normalbuffer);
    glGenBuffers(1, &elementbuffer);
}
void Buffers::DeleteBuffers()
{
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteBuffers(1, &uvbuffer);
    glDeleteBuffers(1, &normalbuffer);
    glDeleteBuffers(1, &elementbuffer);

    glDeleteVertexArrays(1, &VertexArrayObject);
}

// Buffers da tangents
void BuffersTangents::CreateBuffers()
{
    glGenVertexArrays(1, &VertexArrayObject);
    glGenBuffers(1, &vertexbuffer);
    glGenBuffers(1, &uvbuffer);
    glGenBuffers(1, &normalbuffer);
    glGenBuffers(1, &tangentBuffer);
    glGenBuffers(1, &bitangentBuffer);
    glGenBuffers(1, &elementbuffer);
}
void BuffersTangents::DeleteBuffers()
{
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteBuffers(1, &uvbuffer);
    glDeleteBuffers(1, &normalbuffer);
    glDeleteBuffers(1, &tangentBuffer);
    glDeleteBuffers(1, &bitangentBuffer);
    glDeleteBuffers(1, &elementbuffer);

    glDeleteVertexArrays(1, &VertexArrayObject);
}

//
void BuffersTexture::InitBuffers()
{
	glGenVertexArrays(1, &VertexArrayObject);

	glGenBuffers(1, &Text2DVertexBufferID);
	glGenBuffers(1, &Text2DUVBufferID);
}
void BuffersTexture::DeleteBuffer()
{
    glDeleteBuffers(1, &Text2DVertexBufferID);
	glDeleteBuffers(1, &Text2DUVBufferID);

	glDeleteVertexArrays(1, &VertexArrayObject);
}