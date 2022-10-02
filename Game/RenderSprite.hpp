#ifndef RENDERSPRITE_HPP
#define RENDERSPRITE_HPP

class RenderSprite
{
private:
    ShaderProgram shader;

    ImageProgram texture;

    GLuint VertexArrayObject;
    GLuint vertexbuffer;
    GLuint uvsbuffer;
    
    Clock time;
public:
    RenderSprite(string fileTexture);
    void Render(Camera & camera);
    void Update();
    void Delete();
};

#endif