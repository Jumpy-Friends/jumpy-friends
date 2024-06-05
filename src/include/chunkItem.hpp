#pragma once

#include <raylib-cpp.hpp>

class ChunkItem {
   protected:
    float position;
    virtual void Draw(Vector3);
    virtual void Update();
    virtual BoundingBox GetBoundingBox(Vector3 chunkPosition) const;

   public:
    ChunkItem(float initialX) {
        this->position = initialX;
    };
};