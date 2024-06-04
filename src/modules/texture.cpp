#include "texture.hpp"

Texture2D
    TEXTURE_GRASS,
    TEXTURE_SIDEWALK,
    TEXTURE_ROAD,
    TEXTURE_SAND,
    TEXTURE_SEA;

void LoadTextures() {
    TEXTURE_GRASS = LoadTexture("src/assets/textures/grass.png");
    TEXTURE_SIDEWALK = LoadTexture("src/assets/textures/sidewalk.png");
    TEXTURE_ROAD = LoadTexture("src/assets/textures/road.png");
    TEXTURE_SAND = LoadTexture("src/assets/textures/sand.png");
    TEXTURE_SEA = LoadTexture("src/assets/textures/sea.png");
}