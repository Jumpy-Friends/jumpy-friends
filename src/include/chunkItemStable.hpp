#pragma once

#include <raylib-cpp.hpp>

#include "chunkItem.hpp"
#include "models.hpp"

class ChunkItemStable : public ChunkItem {
   public:
    void Draw(Vector3) override;
    void Update() override;
    ChunkItemStable(float position);
    float scale = GetRandomValue(7, 10) / 10.f;
};