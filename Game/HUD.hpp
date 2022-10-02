#ifndef HUD_HPP
#define HUD_HPP

class Hud
{
private:
    ShaderProgram shader;
    ImageProgram texture;

    BuffersTexture buffers;

    mat4 model = mat4(1.0);

    Clock time;

public:
    Hud(string texturePath);
    void Render(Camera & camera);
    void Delete();
};



#endif