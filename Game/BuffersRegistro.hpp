#ifndef BUFFERSREGISTRO_HPP
#define BUFFERSREGISTRO_HPP

typedef struct Buffers
{
    GLuint VertexArrayObject;
    GLuint vertexbuffer;
    GLuint uvbuffer;
    GLuint normalbuffer;
    GLuint elementbuffer;

    void CreateBuffers();
    void DeleteBuffers();

} Buffers;

typedef struct BuffersTangents
{
    GLuint VertexArrayObject;

    GLuint vertexbuffer;
    GLuint uvbuffer;
    GLuint normalbuffer;
    GLuint tangentBuffer;
    GLuint bitangentBuffer;
    
    GLuint elementbuffer;

    void CreateBuffers();
    void DeleteBuffers();

} BuffersTangents;

typedef struct BuffersTexture
{
    GLuint VertexArrayObject;
    GLuint Text2DVertexBufferID;
    GLuint Text2DUVBufferID;
    
    void InitBuffers();
    void DeleteBuffer();
    
} BuffersTexture;


#endif // !BUFFERSREGISTRO_HPP