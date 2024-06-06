#pragma once

#include <raylib-cpp.hpp>

#include "chunkItem.hpp"
#include "models.hpp"

enum MovingChunkItem {
    Car = 0,
    Surfboard = 1
};

class ChunkItemMoving : public ChunkItem {
   public:
    float speedX;
    MovingChunkItem type;
    void Draw(Vector3) override;
    void Update() override;
    Model model;

    ChunkItemMoving(MovingChunkItem type, float speedX, float position) {
        this->type = type;
        this->speedX = speedX;
        this->position = position;
    };
};