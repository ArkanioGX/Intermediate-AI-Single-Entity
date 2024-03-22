#include "raylib.h"
#include "Game.h"

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Raylib basic window");
    SetTargetFPS(60);

    Game* game = new Game();
    game->initialize();

    while (!WindowShouldClose()) {
        game->loop();
        BeginDrawing();
        ClearBackground(RAYWHITE);
        game->draw();
        EndDrawing();
    }
    game->close();
    CloseWindow();
    return 0;
}