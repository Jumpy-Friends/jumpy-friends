#pragma once

#include <raylib-cpp.hpp>

#include "chunkItem.hpp"

enum MovingChunkItem {
    Car = 0,
    Surfboard = 1
};

class ChunkItemMoving : public ChunkItem {
   public:
    float speedX;
    MovingChunkItem type;
    void Draw(Vector3);
    void Update();
    BoundingBox GetBoundingBox(Vector3 chunkPosition) const;

    ChunkItemMoving(MovingChunkItem type, float speedX, float position) : ChunkItem(position) {
        this->type = type;
        this->speedX = speedX;
    };
};