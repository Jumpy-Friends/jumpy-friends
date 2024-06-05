#pragma once

#include <random>
#include <iostream>
#include <deque>
#include <raylib-cpp.hpp>

#include "chunkItemMoving.hpp"
#include "chunkItemStable.hpp"
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
    std::deque<ChunkItem*> items;
    int chunkItemCapacity = 10;
    double itemGenProb = 0.3;
    int chunkItemSpeed;
    

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
        this->setupChunkItems();
    }

    void Despawn();
    void Spawn();
    void Update(double);
    void Draw(ChunkType nextChunk);
    void setPosition(raylib::Vector3);
    void setupChunkItems();
    void updateChunkItems();

    void moveMovingChunkItems();
    void deleteMovingChunkItem();
    void generateMovingChunkItem();  // Remove moving
                                     // Setup -> iterate from -15 to 15
    bool generateBernouilli(double);
   private:
};
