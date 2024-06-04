#pragma once

#include <raylib-cpp.hpp>

class Light {
    Vector3 direction;
    Color color;

   public:
    Light(Vector3 = Vector3{1, -1, -1}, Color color = WHITE) {
        this->direction = direction;
        this->color = color;
    }
};
