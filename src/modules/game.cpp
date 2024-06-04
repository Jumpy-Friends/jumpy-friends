#include "game.hpp"

Game::Game(int width, int height, std::string title) {
    this->window = new raylib::Window(width, height, title);

    SetTargetFPS(60);

    this->camera.position = (Vector3){-4.0f, 7.50f, -5.0f};
    this->camera.target = (Vector3){0.0f, 0.0f, 2.0f};
    this->camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    this->camera.fovy = 40.0f;
    this->camera.projection = CAMERA_PERSPECTIVE;

    // this->shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(shader, "viewPos");

    // float cameraPos[3] = {camera.position.x, camera.position.y, camera.position.z};
    // SetShaderValue(shader, shader.locs[SHADER_LOC_VECTOR_VIEW], cameraPos, SHADER_UNIFORM_VEC3);
}

void Game::isHere() {
    while (!this->window->ShouldClose()) {
        double time = GetTime();
        double deltaTime = GetFrameTime();
        this->PollEvents();

        if (this->gameState == Start){
            this->DisplayStart(time, deltaTime);
        }

        else if (this->gameState == Playing) {
            this->Update(time, deltaTime);
            this->DisplayPlay(time, deltaTime);
        }
        else if (this->gameState == Finish)
            this->DisplayFinish(time, deltaTime);
        
        // UpdateLightValues(shader, light);
    
    }
}



void Game::PollEvents() {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        this->onClick(GetMousePosition());

    if (IsKeyPressed(KEY_UP))
        this->onKeyPress(KEY_UP);
}

void Game::Update(double time, double deltaTime) {
    this->ground.Update();
    this->player.Update();
}

void Game::DisplayStart(double time, double deltaTime) {
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


void Game::onClick(Vector2 position) {
    if (this->gameState == Start) {
        this->gameState = Playing;
    }
    
    else if (this->gameState == Playing){
        this->player.Jump();
    } 
}

void Game::onKeyPress(int key) {
    if (key == KEY_UP)
        this->player.Jump();
}