#include "stdio.h"

#include "raylib.h"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Polly");
    SetTargetFPS(30);

    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Congrats! You created your first window!", 190, 200, 20,
                 LIGHTGRAY);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
