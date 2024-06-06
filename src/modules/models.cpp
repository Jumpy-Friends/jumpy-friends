#include "models.hpp"

Model CAR_MODEL, LOG_MODEL, TREE_MODEL;

void LoadModels() {
    CAR_MODEL = LoadModel("src/models/OBJ/sude.glb");
    LOG_MODEL = LoadModel("src/models/OBJ/log.glb");
    TREE_MODEL = LoadModel("src/models/OBJ/tree_guzel.glb");
}