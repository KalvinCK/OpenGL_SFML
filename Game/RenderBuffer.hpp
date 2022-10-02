#ifndef RENDERBUFFER_HPP
#define RENDERBUFFER_HPP

class RenderBuffer
{
private:
    ShaderProgram shader;

    GLuint renderedTexture;
    GLuint depthrenderbuffer;

    GLuint VertexArrayObject;
    GLuint quad_vertexbuffer;
    Clock tempo;

    GLuint FramebufferName = 0;
public:
    RenderBuffer(ivec2 size);
    void ActiveFrameBuffer(ivec2 Size);
    void Render(ivec2 Size);
    void Delete();
};

#endif // !RENDERTEXTURE_HPP