#include <iostream>
#include <string>
using namespace std;

#include <SOIL/SOIL.h>

#include <GL/glew.h>

#include "ImageProgram.hpp"

void ImageProgram::LoadTexture(string path)
{   
    glGenTextures(1, &handle);
	glBindTexture(GL_TEXTURE_2D, handle);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    int width, height;
    unsigned char* image = SOIL_load_image(path.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
    if(!image)
    {
        cout << "Nao foi possivel carregar a imagen: " << path << endl;
        exit(1);
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

    glGenerateMipmap(GL_TEXTURE_2D);

    SOIL_free_image_data(image);
}
void ImageProgram::Use(TextureUnit unit)
{
    glActiveTexture(unit);
    glBindTexture(GL_TEXTURE_2D, handle);
}
void ImageProgram::DeleteTextures()
{
    glDeleteTextures(1, &handle);
}


GLuint loadTexture(const char* textImagePath) 
{ 
    GLuint textureID;
    textureID = SOIL_load_OGL_texture(textImagePath, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y); 
    if (textureID == 0) 
    cout << "could not find texture file" << textImagePath << endl; 
    return textureID;
}

// load texture with stb_image
//#pragma once
//
//#include <iostream>
//#include <string>
//using namespace std;
//
//#include <stb_image.h>
//
//#include <GL/glew.h>
//
//
//class TextureProgram
//{
//private:
//	GLuint Handle;
//public:
//	void Load(string path, bool gammaCorrection = true)
//    {
//        int width, height, nrComponents;
//        stbi_set_flip_vertically_on_load(true);
//
//        unsigned char* image = stbi_load(path.c_str(), &width, &height, &nrComponents, 4);
//        if (!image)
//        {
//            cout << "Erro imagen nao encontrada: " << path << endl;
//            stbi_image_free(image);
//            exit(EXIT_FAILURE);
//        }
//
//        glGenTextures(1, &Handle);
//        glBindTexture(GL_TEXTURE_2D, Handle);
//
//        //GLenum internal_format = GL_SRGB;
//        //GLenum dataFormat = GL_RGB;
//
//        //if (nrComponents == 3)
//        //{
//        //    internal_format = gammaCorrection ? GL_SRGB : GL_RGB;
//        //    dataFormat = GL_RGB;
//        //    cout << path << "Canais: " << nrComponents << endl;
//        //}
//        //else if (nrComponents == 4)
//        //{
//        //    internal_format = gammaCorrection ? GL_SRGB_ALPHA : GL_RGBA;
//        //    dataFormat = GL_RGBA;
//        //    cout << path << "Canais: " << nrComponents << endl;
//        //}
//
//        /*glTexImage2D(GL_TEXTURE_2D, 0, internal_format, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, image);
//        stbi_image_free(image);*/
//
//        cout << path << " Canais: " << nrComponents << endl;
//
//        glTexImage2D(GL_TEXTURE_2D, 0, gammaCorrection ? GL_SRGB_ALPHA : GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
//        stbi_image_free(image);
//
//
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//        glGenerateMipmap(GL_TEXTURE_2D);
//
//	}
//    void LoadCubeMap(vector<string> cubemap)
//    {
//        int width, height, nrComponents;
//        stbi_set_flip_vertically_on_load(false);
//        
//        glGenTextures(1, &Handle);
//        glBindTexture(GL_TEXTURE_CUBE_MAP, Handle);
//        
//        for (unsigned int i = 0; i < cubemap.size(); i++)
//        {
//        
//            unsigned char* image = stbi_load(cubemap[i].c_str(), &width, &height, &nrComponents, 0);
//            if (!image)
//            {
//                cout << "Erro imagen nao encontrada: " << cubemap[i] << endl;
//                stbi_image_free(image);
//                exit(EXIT_FAILURE);
//            }
//        
//            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
//            stbi_image_free(image);
//        }
//        
//        
//        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
//        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//        
//    }
//    void Use(GLenum unit, GLenum type = GL_TEXTURE_2D)
//    {
//        glActiveTexture(unit);
//        glBindTexture(GL_TEXTURE_2D, Handle);
//    }
//    void Delete()
//    {
//        glDeleteTextures(1, &Handle);
//    }
//};

// load cubeMaps
//int width, height, nrComponents;

//glGenTextures(1, &Handle);
//glBindTexture(GL_TEXTURE_CUBE_MAP, Handle);

//for (unsigned int i = 0; i < cubemap.size(); i++)
//{

//    unsigned char* image = SOIL_load_image(cubemap[i].c_str(), &width, &height, &nrComponents, SOIL_LOAD_RGB);
//    if (!image)
//    {
//        cout << "Erro imagen nao encontrada: " << cubemap[i] << endl;
//        SOIL_free_image_data(image);
//        exit(EXIT_FAILURE);
//    }

//    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
//    SOIL_free_image_data(image);
//}