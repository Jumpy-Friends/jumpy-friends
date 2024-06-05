#include "models.hpp"

Model CAR_MODEL;

void LoadModels() {
    CAR_MODEL = LoadModel("src/models/OBJ/araba1.glb");
}