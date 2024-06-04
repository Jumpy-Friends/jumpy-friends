#pragma once
#include <iostream>
#include <raylib-cpp.hpp>

#include "ground.hpp"
#include "player.hpp"
#include "rlights.h"
#include "startScreen.hpp"
#include "texture.hpp"

#define RENDER_CHUNK_SIZE 30

enum GameState {
    Start,
    Playing,
    Finish
};

class Game {
   private:
    raylib::Window* window;
    Camera3D camera;
    GameState gameState = Start;
    double worldSpeed = 0.02;
    Ground ground = Ground(RENDER_CHUNK_SIZE, this->worldSpeed);
    Player player = Player(this->worldSpeed);

    void DisplayStart(double time, double deltaTime);
    void DisplayPlay(double time, double deltaTime);
    void DisplayFinish(double time, double deltaTime);

    void Update(double time, double deltaTime);
    void PollEvents();
    bool CheckCollisions();

    void onClick(Vector2 position);
    void onKeyPress(int key);

   public:
    Game(int, int, std::string);
    void isHere();
    void Restart();
};