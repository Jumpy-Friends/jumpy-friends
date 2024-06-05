#pragma once

#include <raylib-cpp.hpp>

class ChunkItem {
   public:
    float position;
    virtual void Draw(Vector3) = 0;
    virtual void Update() = 0;

    BoundingBox GetBoundingBox(Vector3 chunkPosition) const {
        Vector3 itemPosition = {this->position, chunkPosition.y + 0.1f, chunkPosition.z};
        Vector3 min = {itemPosition.x - 1.0f, itemPosition.y - 0.5f, itemPosition.z - 0.3f};
        Vector3 max = {itemPosition.x + 1.0f, itemPosition.y + 0.5f, itemPosition.z + 0.3f};
        return BoundingBox{min, max};
    }

    ChunkItem(float initialX) {
        this->position = initialX;
    };

    ChunkItem(){};
};