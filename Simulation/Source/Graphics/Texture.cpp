#include "Graphics/Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <glad/glad.h>

#include <iostream>

unsigned int TextureLoader::New(const char* path)
{
    // load and create a texture 
    // -------------------------
    unsigned int texID;
    glGenTextures(1, &texID);

    int width, height, channel;
    unsigned char* data = stbi_load(path, &width, &height, &channel, 0);
    if (data)
    {
        GLenum format;
        if (channel == 1)
            format = GL_RED;
        else if (channel == 3)
            format = GL_RGB;
        else if (channel == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, texID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
        stbi_image_free(data);
    }

    return texID;
}

void TextureLoader::FlipVertically()
{
    stbi_set_flip_vertically_on_load(true);
}

Texture::Texture(const char* path, std::string name, TextureType type) : mName(name), mFilePath(path), mType(type)
{
    mID = TextureLoader::New(path);
}

unsigned int Texture::ID() const
{
    return mID;
}

std::string Texture::Name() const
{
    return mName;
}

std::string Texture::FilePath() const
{
    return mFilePath;
}

TextureType Texture::Type() const
{
    return mType;
}
