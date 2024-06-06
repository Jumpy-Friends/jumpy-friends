#pragma once

#include <iostream>
#include <raylib-cpp.hpp>

#include "chunk.hpp"

#define JUMP_SPEED 0.1

enum JumpType {
    Forward,
    Left,
    Right,
    Backward,
    None
};

class Player {
   private:
    Vector3 position = Vector3{0, 0.1, 0};
    double worldSpeed;
    double currentSpeed;
    double gravity = -0.02f;
    JumpType jumpType = JumpType::None;
    std::vector<Model> models;
    std::vector<float> scales;
    int currentModelIndex;

   public:
    Player(double speed);
    void Draw();
    void ImportModel(const std::string& path, const std::string& texturePath, float scale);
    void SwitchModel();
    void Update();
    void JumpForward();
    void JumpLeft();
    void JumpRight();
    void JumpBackward();
    void resetPos();
    void followLog(float);
    BoundingBox GetBoundingBox() const;
    Vector3 GetPosition() const;
};