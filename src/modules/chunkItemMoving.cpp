#include "chunkItemMoving.hpp"

#include "player.hpp"

Color movingChunkItemColors[2] = {RED, BROWN};

void ChunkItemMoving::Update() {
    this->position -= speedX;
}

void ChunkItemMoving::Draw(Vector3 chunkPosition) {
    raylib::Vector3 itemPosition = raylib::Vector3(this->position, chunkPosition.y + 0.1, chunkPosition.z);

    if (this->type == Surfboard) {
        DrawModelEx(LOG_MODEL, itemPosition, Vector3{1, 1, 1}, 0, Vector3{0.75, 0.75, 0.75}, WHITE);
    } else {
        DrawModelEx(CAR_MODEL, itemPosition, Vector3{1, 1, 1}, 0, Vector3{0.75, 0.75, 0.75}, this->tint);
    }
}
