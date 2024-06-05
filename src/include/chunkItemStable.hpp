#pragma once

#include <raylib-cpp.hpp>

#include "chunkItem.hpp"

class ChunkItemStable : public ChunkItem {
   public:
    void Draw(Vector3) override;
    void Update() override;
    ChunkItemStable(float position);
};