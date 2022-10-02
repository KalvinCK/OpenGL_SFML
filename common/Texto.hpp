#ifndef TEXTO_HPP
#define TEXTO_HPP

class Texto
{
private:
    ShaderProgram shader;
    ImageProgram texture;

    GLuint VertexArrayObject;
    GLuint Text2DVertexBufferID;
    GLuint Text2DUVBufferID;

public:
    void initText2D(string texturePath);
    void printText2D(string text, vec3 color, int x, int y, int size);
    void Delete();
};



#endif