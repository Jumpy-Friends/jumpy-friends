#pragma once
#include <iostream>
#include <raylib-cpp.hpp>

#include "chunkItemMoving.hpp"
#include "ground.hpp"
#include "models.hpp"
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
    double worldSpeed = 0.04;
    int score;
    Ground ground = Ground(RENDER_CHUNK_SIZE, this->worldSpeed);
    Player player = Player(this->worldSpeed);

    void DisplayStart(double time, double deltaTime);
    void DisplayPlay(double time, double deltaTime);
    void DisplayFinish(double time, double deltaTime);

    void Update(double time, double deltaTime);
    void PollEvents();

    bool CheckMovingCollisions();
    bool CheckStaticCollisions(float, float);
    bool CheckCollisions(MovingChunkItem&, float&);


    void onClick(Vector2 position);
    void onKeyPress(int key);
    ChunkType currentPlayerChunk();

   public:
    Game(int, int, std::string);
    void isHere();
    void Restart();
    void IncrementScore(int amount);
    bool IsOutOfBounds(Vector3 pos);
};