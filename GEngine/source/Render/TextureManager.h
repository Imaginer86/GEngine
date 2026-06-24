#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>

#define GLEW_STATIC
#include <GL/glew.h>

struct TextureSettings {
    GLint wrapS = GL_REPEAT;
    GLint wrapT = GL_REPEAT;
    GLint minFilter = GL_LINEAR_MIPMAP_LINEAR;
    GLint magFilter = GL_LINEAR;
    bool generateMipmaps = true;
    bool flipVertically = true;
    bool srgb = false;

    // Leave as 0 to infer from the loaded image channels.
    GLenum internalFormat = 0;
    GLenum dataFormat = 0;
};

struct Texture2D {
    GLuint id = 0;
    int width = 0;
    int height = 0;
    int channels = 0;
    std::string path;
};

class TextureManager final {
public:
    static TextureManager& instance();

    TextureManager(const TextureManager&) = delete;
    TextureManager& operator=(const TextureManager&) = delete;
    TextureManager(TextureManager&&) = delete;
    TextureManager& operator=(TextureManager&&) = delete;

    GLuint load(const std::string& name,
                const std::string& path,
                const TextureSettings& settings = TextureSettings{});

    const Texture2D& get(const std::string& name) const;
    bool contains(const std::string& name) const;

    void bind(const std::string& name, GLenum textureUnit = GL_TEXTURE0) const;
    void unload(const std::string& name);
    void clear();

private:
    TextureManager() = default;
    ~TextureManager();

    std::unordered_map<std::string, Texture2D> textures_;
};