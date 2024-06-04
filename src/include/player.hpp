#pragma once

#include <iostream>
#include <raylib-cpp.hpp>

class Player {
   private:
    raylib::Material material;
    Vector3 position = Vector3{0, 0.25, 0};
    double worldSpeed;
    double jumpSpeed;
    double gravity = -0.01f;
    double zProgress = 0;
    double movement = -1;
    bool jumped = false;

   public:
    Player(double speed);
    void Draw();
    void Update();
    void Jump();
};