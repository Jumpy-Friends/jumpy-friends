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
    
  
    for(ChunkItem* item: items){
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


void Chunk::setupChunkItems(){

    for (int i = 0; i < this->chunkItemCapacity; i++){
        
        ChunkItem* newItem;
        if (this->type == River || this->type == Road) {
            if(!this->generateBernouilli(this->itemGenProb)){
                continue;
            }

            MovingChunkItem type = Car;
            if (this->type == River) {
                type = Surfboard;
            }
            newItem = new ChunkItemMoving(type, 0.5f, -6.f + ((i + 1) * 4.0f));
        }
        else {
            if(!this->generateBernouilli(this->itemGenProb)){
                continue;
            }
            newItem = new ChunkItemStable(-6.f + ((i + 1) * 4.0f));
        }
        this->items.push_back(newItem);
    }
}

void Chunk::updateChunkItems(){
    if (this->type == River || this->type == Road) {
        this->deleteMovingChunkItem();
        this->generateMovingChunkItem();
        this->moveMovingChunkItems();
    }
}

//

void Chunk::deleteMovingChunkItem(){
    if(!items.empty()){
        ChunkItem* mightDelete = items.front();
        std::cout << mightDelete->position << std::endl;
        if(mightDelete->position > 15.0 || mightDelete->position < -15.0 ){
        std::cout << "deleting item" << std::endl;
        items.pop_front();
        }
    }
}

void Chunk::generateMovingChunkItem() {
    // the list is full
   
    std::cout << this->items.size()<< std::endl;
    if (this->chunkItemCapacity == this->items.size()) return;
     
    MovingChunkItem type = Car;

    if (this->type == River) {
        type = Surfboard;
        this->items.push_back(new ChunkItemMoving(type, 0.5, -14.0 + ((this->items.size()+ 1) * 4.0)));

    }

    this->items.push_back(new ChunkItemMoving(type, 0.5, -14.0 + ((this->items.size()+ 1) * 4.0)));
}

void Chunk::moveMovingChunkItems(){
    if (this->type == Road || this->type == River) {
        for(ChunkItem* item: items){
            item->Update();
        }
    }
}

bool Chunk::generateBernouilli(double succesP){
    std::random_device rd;
    std::mt19937 gen(rd());

    std::bernoulli_distribution d(succesP);

    bool bernoulli_random_variable = d(gen);

    return bernoulli_random_variable;
}
