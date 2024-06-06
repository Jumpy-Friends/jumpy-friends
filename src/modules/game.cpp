#include "game.hpp"

Game::Game(int width, int height, std::string title) {
    this->window = new raylib::Window(width, height, title);

    this->player.ImportModel("src/models/OBJ/plane.obj", "src/models/OBJ/plane_diffuse.png", 0.015f);
    this->player.ImportModel("src/models/OBJ/castle.obj", "src/models/OBJ/castle_diffuse.png", 0.020f);
    this->player.ImportModel("src/models/OBJ/well.obj", "src/models/OBJ/well_diffuse.png", 0.12f);
    this->player.ImportModel("src/models/OBJ/turret.obj", "src/models/OBJ/turret_diffuse.png", 0.06f);

    SetTargetFPS(60);

    this->camera.position = (Vector3){-4.0f, 7.50f, -5.0f};
    this->camera.target = (Vector3){0.0f, 0.0f, 2.0f};
    this->camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    this->camera.fovy = 40.0f;
    this->camera.projection = CAMERA_PERSPECTIVE;
}

void Game::Restart() {

    this->ground = Ground(RENDER_CHUNK_SIZE, this->worldSpeed);
    this->gameState = Playing;
    this->player.resetPos();
}

void Game::isHere() {
    LoadTextures();

    while (!this->window->ShouldClose()) {
        double time = GetTime();
        double deltaTime = GetFrameTime();
        this->PollEvents();

        if (this->gameState == Start) {
            this->DisplayStart(time, deltaTime);
        }

        else if (this->gameState == Playing) {
            this->Update(time, deltaTime);
            this->DisplayPlay(time, deltaTime);
        } else if (this->gameState == Finish)
            this->DisplayFinish(time, deltaTime);
    }
}

void Game::PollEvents() {

    if (this->gameState == Finish && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        this->Restart();
        return;
    }
    

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        this->onClick(GetMousePosition());

    if (IsKeyPressed(KEY_UP))
        this->onKeyPress(KEY_UP);

    if (IsKeyPressed(KEY_LEFT))
        this->onKeyPress(KEY_LEFT);

    if (IsKeyPressed(KEY_RIGHT))
        this->onKeyPress(KEY_RIGHT);

    if (IsKeyPressed(KEY_DOWN))
        this->onKeyPress(KEY_DOWN);

    if (IsKeyPressed(KEY_S))
        this->onKeyPress(KEY_S);
}

void Game::Update(double time, double deltaTime) {

    this->ground.Update();
    this->player.Update();
    
    if (CheckMovingCollisions()) {
        std::cout << "Game Over!" << std::endl;
        this->gameState = Finish;
    }
}

void Game::DisplayStart(double time, double deltaTime) {
    BeginDrawing();
    {
        ClearBackground(Color{0, 232, 0, 1});
        BeginMode3D(camera);
        {

          this->ground.Draw();
          this->player.Draw();      

        }
        EndMode3D();
      
        StartScreen::draw();
    }
    EndDrawing();
}

void Game::DisplayPlay(double time, double deltaTime) {
    BeginDrawing();
    {
        ClearBackground(Color{0, 232, 0, 1});
        BeginMode3D(camera);
        {
            // DrawGrid(40, 0.5f);
            this->ground.Draw();
            this->player.Draw();
        }
        EndMode3D();
        
    }
    EndDrawing();
}

void Game::DisplayFinish(double time, double deltaTime) {
    BeginDrawing();
    {
        ClearBackground(BLACK);
        DrawText("Game Over!", GetScreenWidth() / 2 - MeasureText("Game Over!", 60) / 2, GetScreenHeight() / 2 - 30, 60, RED);
        DrawText("Click to Restart", GetScreenWidth() / 2 - MeasureText("Click to Restart", 20) / 2, GetScreenHeight() / 2 + 40, 20, GRAY);

    }
    EndDrawing();
}

void Game::onClick(Vector2 position) {

    if (this->gameState == Start) {
        this->gameState = Playing;
        return;
    }
    
}

void Game::onKeyPress(int key) {

    if (this->gameState == Playing) {

        if (key == KEY_UP) {
            if (!this->CheckStaticCollisions(0.f, 1.0f)){
                this->player.JumpForward();
            }
            return;
        }

        if (key == KEY_LEFT) {
            if (!this->CheckStaticCollisions(1.0f, 0.f)){
                this->player.JumpLeft();
            }
            return;
        }

        if (key == KEY_RIGHT) {
            if (!this->CheckStaticCollisions(-1.0f, 0.f)){
                this->player.JumpRight();
            }
            return;
        }

        if (key == KEY_DOWN) {
            if (!this->CheckStaticCollisions(0.f, -1.0f)){
                this->player.JumpBackward();
            }
            return;
        }

        if (key == KEY_S) {
            this->player.SwitchModel();
            return;
        }
    }
}


bool Game::CheckMovingCollisions() {
    BoundingBox playerBox = this->player.GetBoundingBox();
    const auto& chunks = this->ground.getChunks();  

    for (const auto& chunk : chunks) {
        if (chunk.type == Road || chunk.type == River){
            for(ChunkItem* item: chunk.items){
               BoundingBox itemBox = item->GetMovingBoundingBox(chunk.position);
               if (CheckCollisionBoxes(playerBox, itemBox)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Game::CheckStaticCollisions(float xOffset, float zOffset) {
    Vector3 currentPosition = player.position;
    Vector3 newPosition = Vector3{currentPosition.x + xOffset, currentPosition.y, currentPosition.z + zOffset};
    
    const auto& chunks = this->ground.getChunks();  

    for (const auto& chunk : chunks) {
        if (!(chunk.type == Road || chunk.type == River)){
            for(ChunkItem* item: chunk.items){
                Vector3 chunkPosition = chunk.position;
                
                float itemXPosition = item->position;

                Vector3 itemPosition = Vector3{itemXPosition, chunkPosition.y, chunkPosition.z};

                if(abs(itemPosition.x - newPosition.x) < 0.5 && abs(itemPosition.z - newPosition.z) < 0.5){
                    return true;
                }

            }
        }
    }
    return false;
}




