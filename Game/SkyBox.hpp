#ifndef SKYBOX_HPP
#define SKYBOX_HPP

class SkyBox
{
private:
    ShaderProgram shader;
    ImageProgram texture;

    ModelIndexer modeloIndexado;
    Buffers buffers;

    Clock time;

public:
    SkyBox(string FileObj, string fileTexture0);
    void Render(Camera & camera);
    void Delete();

};


#endif