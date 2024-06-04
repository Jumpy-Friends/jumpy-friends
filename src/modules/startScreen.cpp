#include "startScreen.hpp"

    extern int StartScreen::gameLogoFontSize = 50;
    extern int StartScreen::gameLogoStrokeFontSize = 50;
    extern int StartScreen::startFontSize = 20;

    void StartScreen::draw() {

        DrawText("Jumpy Friends", (GetScreenWidth() - MeasureText("Jumpy Friends",gameLogoStrokeFontSize))/2 + 4, GetScreenHeight()/4 + 4, gameLogoStrokeFontSize, BLACK);
        DrawText("Jumpy Friends", (GetScreenWidth() - MeasureText("Jumpy Friends", gameLogoFontSize))/2, GetScreenHeight()/4, gameLogoFontSize, ORANGE);
        DrawText("Click to Start...", (GetScreenWidth() - MeasureText("Click to Start", startFontSize))/2, GetScreenHeight() - 100, startFontSize, WHITE);
        
    }

