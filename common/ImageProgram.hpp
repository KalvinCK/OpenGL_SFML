#ifndef IMAGEPROGRAM_HPP
#define IMAGEPROGRAM_HPP

enum TextureUnit
{
    Texture0 = GL_TEXTURE0,
    Texture1 = GL_TEXTURE1,
    Texture2 = GL_TEXTURE2,
    Texture3 = GL_TEXTURE3,
    Texture4 = GL_TEXTURE4
};

class ImageProgram
{
private:
    GLuint handle;
public:
    void LoadTexture(string path);
    void Use(TextureUnit unit);
    void DeleteTextures();
};

#endif // !IMAGEPROGRAM_HPP
