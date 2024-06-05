#include "chunkItemMoving.hpp"

Color movingChunkItemColors[2] = {RED, BROWN};

void ChunkItemMoving::Draw(Vector3 chunkPosition) {
    raylib::Vector3 itemPosition = raylib::Vector3(this->position, chunkPosition.y + 0.1, chunkPosition.z);

    itemPosition.DrawCube(2.0, 1.0, 0.6, movingChunkItemColors[this->type]);
}

void ChunkItemMoving::Update() {
    this->position += speedX;
}
