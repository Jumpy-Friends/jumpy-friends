#include "chunkItemStable.hpp"

ChunkItemStable::ChunkItemStable(float position) {
    this->position = position;
}

void ChunkItemStable::Update() {
}

void ChunkItemStable::Draw(Vector3 chunkPosition) {
    raylib::Vector3 itemPosition = raylib::Vector3(this->position, chunkPosition.y, chunkPosition.z);

    DrawModelEx(TREE_MODEL, itemPosition, Vector3{1, 1, 1}, 0, Vector3{1, scale, 1}, WHITE);
}
