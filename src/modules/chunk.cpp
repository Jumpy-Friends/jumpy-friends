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

    for (ChunkItem* item : items) {
        item->Draw(this->position);
    }
}

void Chunk::Update(double speed) {
    this->position.z -= speed;
    this->updateChunkItems();
}

void Chunk::Despawn() {}

void Chunk::setPosition(raylib::Vector3 position) {
    this->position = position;
}

void Chunk::setupChunkItems() {
    for (int i = -25; i < this->chunkItemCapacity - 25; i++) {
        double random = GetRandomValue(0, 1000) / 1000.f;

        double generationProbability = this->type == River || this->type == Road ? DYNAMIC_DENSITY : STABLE_DENSITY;

        if (!isbetween<double>(random, 0.f, generationProbability)) continue;

        ChunkItem* newItem;

        if (this->type == River || this->type == Road) {
            MovingChunkItem type = Car;
            if (this->type == River)
                type = Surfboard;

            newItem = new ChunkItemMoving(type, this->speed, ((i - 10) * 5.0f));
        } else {
            newItem = new ChunkItemStable(GetRandomValue(3, 5) * i);
        }

        this->items.push_back(newItem);
    }
}

void Chunk::updateChunkItems() {
    if (this->type == River || this->type == Road) {
        this->moveMovingChunkItems();
    }
}

void Chunk::moveMovingChunkItems() {
    if (this->type == Road || this->type == River) {
        for (ChunkItem* item : items) {
            item->Update();
        }
    }
}

bool Chunk::generateBernouilli(double succesP) {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::bernoulli_distribution d(succesP);

    bool bernoulli_random_variable = d(gen);

    return bernoulli_random_variable;
}
