#include "chunk.hpp"

std::ostream& operator<<(std::ostream& os, const Chunk& chunk) {
    return os << "ChunkType: " << chunk.type << std::endl;
}

void Chunk::Draw(ChunkType nextChunk) {
    raylib::Mesh plane = GenMeshPlane(1, 1, 2, 2);
    Model model = LoadModelFromMesh(plane);

    if (this->type == RoadBegin || this->type == RoadEnd)
        model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = TEXTURE_SIDEWALK;
    else if (this->type == Road)
        model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = TEXTURE_ROAD;
    else if (this->type == RiverBegin || this->type == RiverEnd)
        model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = TEXTURE_SAND;
    else if (this->type == River)
        model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = TEXTURE_SEA;
    else
        model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = TEXTURE_GRASS;

    for (int i = -15; i < 15; i++) {
        Vector3 tilePosition = this->position;
        tilePosition.x -= i;
        DrawModel(model, tilePosition, 1, WHITE);

        if (this->type == Road && nextChunk == Road) {
            tilePosition.y += 0.01;
            tilePosition.z += 0.5;
            DrawPlane(tilePosition, Vector2{0.6, 0.075}, WHITE);
        }
    }

    if (this->type == Road || this->type == River) {
        for (int d = 0; d < this->movingItemsNum; d++) {
            int idx = (startIdx + d) % this->movingItemCapacity;
            this->movingItems[idx]->Draw(this->position);
        }
    }
}

void Chunk::Update(double speed) {
    this->generateMovingChunkItem();

    this->position.z -= speed;
    if (this->type == Road || this->type == River) {
        for (int d = 0; d < this->movingItemsNum; d++) {
            int idx = (startIdx + d) % this->movingItemCapacity;
            this->movingItems[idx]->Update();
        }
    }
}

void Chunk::Despawn() {}

void Chunk::setPosition(raylib::Vector3 position) {
    this->position = position;
}

void Chunk::generateMovingChunkItem() {
    // the list is full
    if (this->movingItemCapacity == this->movingItemsNum) return;
    MovingChunkItem type = Car;

    if (this->type == River) {
        type = Surfboard;
    }

    this->movingItems[endIdx] = new ChunkItemMoving(type, 0.01, -6.0 + (this->movingItemsNum * 4.0));
    endIdx = (endIdx + 1) % this->movingItemCapacity;
    this->movingItemsNum += 1;
}
