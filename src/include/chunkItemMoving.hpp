#pragma once

#include <iostream>
#include <raylib-cpp.hpp>

enum MovingChunkItem {
    Car = 0,
    Surfboard = 1
};

class ChunkItemMoving {
   public:
    float position;
    float speedX;
    MovingChunkItem type;
    void draw(Vector3);
    void update();
    ChunkItemMoving(MovingChunkItem, float, float);
    ~ChunkItemMoving();
    BoundingBox GetBoundingBox(Vector3 chunkPosition) const;
};