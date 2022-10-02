#ifndef CREATEOBJECT_HPP
#define CREATEOBJECT_HPP

class CreateObject
{
private:
    ModelIndexer modeloIndexado;

    ShaderProgram shader;
    ImageProgram texture0;
    Buffers buffers;

    Clock time;
    Movement moves[6];
public:
    vec3 position = vec3(0.0f);

    CreateObject(const char * FileObj, string fileTexture0);
    void Render(Camera & camera);
    void Update();
    void Delete(); // destruir

};

#endif