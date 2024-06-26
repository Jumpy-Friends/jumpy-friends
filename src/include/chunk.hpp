#pragma once

#include <deque>
#include <iostream>
#include <random>
#include <raylib-cpp.hpp>

#include "chunkItemMoving.hpp"
#include "chunkItemStable.hpp"
#include "texture.hpp"
#include "utils.hpp"

#define STABLE_DENSITY 0.2f
#define DYNAMIC_DENSITY 0.5f

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

    int chunkItemCapacity = 50;
    double speed = 0.001;

    ChunkType type;
    raylib::Vector3 position;
    ChunkState state;

    Chunk() {
        this->type = FreeWalk;
        this->state = JustExisting;
        this->position = Vector3{6, 0, 0};
    }

    Chunk(ChunkType type, ChunkState state, double speed = 0.03, raylib::Vector3 position = {6, 0, 0}) {
        this->type = type;
        this->state = state;
        this->position = position;
        this->speed = speed;

        if (type == River)
            this->speed *= GetRandomValue(0, 1) == 0 ? 1 : -1;

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
    void generateMovingChunkItem();

   private:
};
