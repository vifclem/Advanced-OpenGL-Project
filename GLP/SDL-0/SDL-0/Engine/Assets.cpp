#include "Assets.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <memory>

// Instantiate static variables
std::map<std::string, Texture2D> Assets::textures;
std::map<std::string, TextureKtx> Assets::ktxTextures;


Texture2D Assets::loadTexture(const std::string &file, const std::string &name) {
    textures[name] = loadTextureFromFile(file.c_str());
    return textures[name];
}

Texture2D& Assets::getTexture(const std::string &name) {
    return textures[name];
}

void Assets::clear() {
    // (Properly) delete all textures
    for (auto iter : textures)
        glDeleteTextures(1, &iter.second.id);
    for (auto iter : ktxTextures)
        glDeleteTextures(1, &iter.second.id);
}

TextureKtx Assets::loadTextureKtx(const std::string &file, const std::string &name) {
    auto texture = TextureKtx();
    texture.load(file.c_str(), texture.id);
    ktxTextures[name] = texture;
    return ktxTextures[name];
}

TextureKtx& Assets::getTextureKtx(const std::string &name) {
    return ktxTextures[name];
}

Texture2D Assets::loadTextureFromFile(const std::string &file) {
    // Create Texture object
    Texture2D texture;
    texture.load(file);

    // Now generate texture
    texture.generate();
    // And finally return texture
    return texture;
}