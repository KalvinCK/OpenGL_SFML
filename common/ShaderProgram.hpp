#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP


class ShaderProgram
{
private:
    GLuint Handle = 0;
    map<string, GLuint> uniformLocations;
    void checkingUniform(const char * name);
public:

    void CreateShader(string vertexShaderFile, string fragmentShaderFile);
    void Use();
    void DeleteProgramShader();

    int GetAtributeLocation(const char * name);

    void SetTexture(const char * name, int data);

    void SetFloat(const char * name, float data);
    void setInt(const char * name, int data);

    void SetVec2(const char * name, vec2 data);
    void SetVec3(const char * name, vec3 data);
    void SetVec4(const char * name, vec4 data);

    void SetMatrix3(const char * name, mat3 data);
    void SetMatrix4(const char * name, mat4 data);
};

#endif