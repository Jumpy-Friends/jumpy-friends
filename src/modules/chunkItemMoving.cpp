#include "chunkItemMoving.hpp"
#include "player.hpp"

Color movingChunkItemColors[2] = {RED, BROWN};

ChunkItemMoving::~ChunkItemMoving() {
    free(this);
}

ChunkItemMoving::ChunkItemMoving(MovingChunkItem type, float speedX, float position) {
    this->type = type;
    this->speedX = speedX;
    this->position = position;

}

void ChunkItemMoving::draw(Vector3 chunkPosition) {
    raylib::Vector3 itemPosition = raylib::Vector3(this->position, chunkPosition.y + 0.1, chunkPosition.z);
    
    DrawModelEx(CAR_MODEL, itemPosition, Vector3{1, 1, 1}, 0, Vector3{0.6, 0.3, 0.3}, movingChunkItemColors[this->type]);
    //DrawModelEx(CAR_MODEL, itemPosition, Vector3{1, 0, 0}, 270, Vector3{0.09, 0.09, 0.09}, movingChunkItemColors[this->type]);
    //itemPosition.DrawCube(2.0, 1.0, 0.6, movingChunkItemColors[this->type]);
}

void ChunkItemMoving::update() {
    this->position += speedX;
}

BoundingBox ChunkItemMoving::GetBoundingBox(Vector3 chunkPosition) const {
    Vector3 itemPosition = { this->position, chunkPosition.y + 0.1f, chunkPosition.z };
    Vector3 min = { itemPosition.x - 1.0f, itemPosition.y - 0.5f, itemPosition.z - 0.3f };
    Vector3 max = { itemPosition.x + 1.0f, itemPosition.y + 0.5f, itemPosition.z + 0.3f };
    return BoundingBox{ min, max };
}