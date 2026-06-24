#include "TextureManager.h"

#include <stdexcept>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>



namespace {

GLenum inferDataFormat(int channels) {
    switch (channels) {
    case 1:
        return GL_RED;
    case 2:
        return GL_RG;
    case 3:
        return GL_RGB;
    case 4:
        return GL_RGBA;
    default:
        throw std::runtime_error("Unsupported texture channel count: " + std::to_string(channels));
    }
}

GLenum inferInternalFormat(int channels, bool srgb) {
    switch (channels) {
    case 1:
        return GL_R8;
    case 2:
        return GL_RG8;
    case 3:
        return srgb ? GL_SRGB8 : GL_RGB8;
    case 4:
        return srgb ? GL_SRGB8_ALPHA8 : GL_RGBA8;
    default:
        throw std::runtime_error("Unsupported texture channel count: " + std::to_string(channels));
    }
}

} // namespace

TextureManager::~TextureManager() {
    clear();
}

TextureManager& TextureManager::instance() {
    static TextureManager textureManager;
    return textureManager;
}

GLuint TextureManager::load(const std::string& name,
                            const std::string& path,
                            const TextureSettings& settings) {
    if (name.empty()) {
        throw std::runtime_error("Texture name cannot be empty");
    }

    const auto existing = textures_.find(name);
    if (existing != textures_.end()) {
        return existing->second.id;
    }

    stbi_set_flip_vertically_on_load(settings.flipVertically ? 1 : 0);

    int width = 0;
    int height = 0;
    int channels = 0;
    unsigned char* pixels = stbi_load((path + "/" + name + ".png").c_str(), &width, &height, &channels, 0);
    if (!pixels) {
        const char* reason = stbi_failure_reason();
        throw std::runtime_error("Failed to load texture '" + path + "': " +
                                 (reason != nullptr ? reason : "unknown stb_image error"));
    }

    const GLenum dataFormat = settings.dataFormat != 0
        ? settings.dataFormat
        : inferDataFormat(channels);
    const GLenum internalFormat = settings.internalFormat != 0
        ? settings.internalFormat
        : inferInternalFormat(channels, settings.srgb);

    GLuint textureId = 0;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, settings.wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, settings.wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, settings.minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, settings.magFilter);

    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 internalFormat,
                 width,
                 height,
                 0,
                 dataFormat,
                 GL_UNSIGNED_BYTE,
                 pixels);

    if (settings.generateMipmaps) {
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(pixels);

    textures_.emplace(name, Texture2D{
        textureId,
        width,
        height,
        channels,
        path,
    });

    return textureId;
}

const Texture2D& TextureManager::get(const std::string& name) const {
    const auto it = textures_.find(name);
    if (it == textures_.end()) {
        throw std::runtime_error("Texture not found: " + name);
    }
    return it->second;
}

bool TextureManager::contains(const std::string& name) const {
    return textures_.find(name) != textures_.end();
}

void TextureManager::bind(const std::string& name, GLenum textureUnit) const {
    const Texture2D& texture = get(name);
    glActiveTexture(textureUnit);
    glBindTexture(GL_TEXTURE_2D, texture.id);
}

void TextureManager::unload(const std::string& name) {
    const auto it = textures_.find(name);
    if (it == textures_.end()) {
        return;
    }

    if (it->second.id != 0) {
        glDeleteTextures(1, &it->second.id);
    }
    textures_.erase(it);
}

void TextureManager::clear()
{
    for (auto& pair : textures_)
    {
        auto& texture = pair.second;

        if (texture.id != 0)
        {
            glDeleteTextures(1, &texture.id);
            texture.id = 0;
        }
    }

    textures_.clear();
}