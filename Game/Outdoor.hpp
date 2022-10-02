#ifndef OUTDOOR_HPP
#define OUTDOOR_HPP

class Outdoor
{
private:
    ShaderProgram shader;

    ImageProgram texture;

    GLuint VertexArrayObject;
    GLuint vertexbuffer;
    
    float LifeLevel = 0;
public:
    vec3 position = vec3(0.0f);
    Outdoor(string fileTexture);
    void Render(Camera & camera);
    void Update();
    void Delete();
};

#endif // !OUTDOORS_HPP