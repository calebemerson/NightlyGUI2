#include "TextureManager.h"

map<string, Texture> TextureManager::textures;   // so file knows it exists with static variables

void TextureManager::LoadTexture(string textureName) {

    string path = "srcImg/";
    path += textureName + ".png";
    textures[textureName].loadFromFile(path);
}

Texture &TextureManager::GetTexture(string textureName) {

    if (textures.find(textureName) == textures.end()){   // if the texture is not there, we load it.
        LoadTexture(textureName);
    }
    return textures[textureName];
}

void TextureManager::Clear() {

    textures.clear();     // rids of all stored objects.
}

