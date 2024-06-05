#pragma once

#include <iostream>
#include <raylib-cpp.hpp>

#include "chunkItemMoving.hpp"
#include "texture.hpp"

enum ChunkType {
    FreeWalk,
    RoadBegin,
    Road,
    RoadEnd,
    RiverBegin,
    River,
    RiverEnd,
};

enum ChunkState {
    Spawning,
    Despawning,
    JustExisting
};

struct Chunk {
    ChunkItemMoving* movingItems[10];
    int movingItemCapacity = 10;
    int movingItemsNum = 0;
    int startIdx = 0;
    int endIdx = 0;

    ChunkType type;
    raylib::Vector3 position;
    ChunkState state;

    Chunk() {
        this->type = FreeWalk;
        this->state = JustExisting;
        this->position = Vector3{6, 0, 0};
    }

    Chunk(ChunkType type, ChunkState state, raylib::Vector3 position = {6, 0, 0}) {
        this->type = type;
        this->state = state;
        this->position = position;
        if (this->type == Road || this->type == River) {
            this->generateMovingChunkItem();
        }
    }

    void Despawn();
    void Spawn();
    void Update(double);
    void Draw(ChunkType nextChunk);
    void setPosition(raylib::Vector3);
    void generateMovingChunkItem();  // Remove moving
                                     // Setup -> iterate from -15 to 15

   private:
};
