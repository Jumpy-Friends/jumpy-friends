#include "models.hpp"

Model CAR_MODEL, LOG_MODEL;

void LoadModels() {
    CAR_MODEL = LoadModel("src/models/OBJ/sude.glb");
    LOG_MODEL = LoadModel("src/models/OBJ/log.glb");
}