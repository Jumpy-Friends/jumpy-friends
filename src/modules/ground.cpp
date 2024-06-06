#include "ground.hpp"

Ground::Ground(int chunkCount, double worldSpeed) {
    if (chunkCount < 5) throw "Chunk count should be bigger than 5.";

    this->worldSpeed = worldSpeed;
    this->SetupGround(chunkCount);
}

void Ground::SetupGround(int chunkCount) {
    int i;
    for (i = -4; i < 8; i++) {
        Chunk freewalk = Chunk{FreeWalk, JustExisting, 0, Vector3{0, 0, (float)i}};
        this->chunks.push_back(freewalk);
    }

    for (i; i < chunkCount; i++) {
        Chunk collapsedChunk = this->collapseNextChunk();
        collapsedChunk.position = Vector3{0, 0, (float)i};
        this->chunks.push_back(collapsedChunk);
    }
}

Chunk Ground::collapseNextChunk() {
    double random = 0.f;

    double speed = 0.05;

    switch (this->getLastChunk().type) {
        // Lowest energy collapses (deterministic).
        case RoadBegin:
            return Chunk{Road, JustExisting};

        case RiverBegin:
            return Chunk{River, JustExisting};

        case RoadEnd:
        case RiverEnd:
            return Chunk{FreeWalk, JustExisting};

        case FreeWalk:
            random = GetRandomValue(0, 1000) / 1000.f;
            return isbetween<double>(random, 0.f, 0.5)
                       ? Chunk{FreeWalk, JustExisting}
                   : isbetween<double>(random, 0.5, 0.8)
                       ? Chunk{RoadBegin, JustExisting}
                       : Chunk{RiverBegin, JustExisting};

        case Road:
            if (this->chunks.at(this->chunks.size() - 2).type == RoadBegin)
                return Chunk{Road, JustExisting, speed};
            random = GetRandomValue(0, 1000) / 1000.f;
            return isbetween<double>(random, 0.f, 0.5)
                       ? Chunk{Road, JustExisting, speed}
                       : Chunk{RoadEnd, JustExisting};

        case River:
            if (this->chunks.at(this->chunks.size() - 2).type == RiverBegin)
                return Chunk{River, JustExisting, speed};
            random = GetRandomValue(0, 1000) / 1000.f;
            return isbetween<double>(random, 0.f, 0.6)
                       ? Chunk{River, JustExisting, speed}
                       : Chunk{RiverEnd, JustExisting};
    }
}

void Ground::Step() {
    this->chunks.erase(this->chunks.begin());

    raylib::Vector3 lastPosition = this->getLastChunk().position;
    Chunk next = this->collapseNextChunk();
    next.position = Vector3{0, 0, lastPosition.z + 1};
    this->chunks.push_back(next);
}

void Ground::Update() {
    for (auto chunk = this->chunks.begin(); chunk != this->chunks.end(); chunk++)
        chunk->Update(this->worldSpeed);

    if (this->chunks[0].position.z < -10) this->Step();
}

void Ground::Draw() {
    for (int i = 0; i < this->chunks.size() - 1; i++)
        this->chunks.at(i).Draw(this->chunks.at(i + 1).type);
}

Chunk Ground::getLastChunk() {
    return this->chunks[this->chunks.size() - 1];
}

void Ground::PrintChunks() {
    for (int i = 0; i < this->chunks.size(); i++) {
        std::cout << i << ": " << this->chunks[i].type << std::endl;
    }
}

const std::vector<Chunk>& Ground::getChunks() const {
    return this->chunks;
}