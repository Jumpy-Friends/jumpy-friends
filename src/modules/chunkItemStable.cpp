#include "chunkItemStable.hpp"

ChunkItemStable::ChunkItemStable(float position) {
    this->position = position;
}

void ChunkItemStable::Update() {
}

void ChunkItemStable::Draw(Vector3 chunkPosition) {
    raylib::Vector3 itemPosition = raylib::Vector3(this->position, chunkPosition.y, chunkPosition.z);

    itemPosition.DrawCube(1.0, 1.0, 1.0, BLACK);
}
