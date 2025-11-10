#include "stdio.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "general.h"
#include "raylib.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./polly [path-to-slides.md].\n");
        exit(0);
    }

    ///////////////////////////////////////////////////////////////////////////
    // Read in the markdown file

    ///////////////////////////////////////////////////////////////////////////
    // Start raylib application
    bool show_slide_number = true;
    int slide_index = 0; // temp
    int num_slides = 30; // temp

    const int default_width = 1080;
    const int default_height = 720;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(default_width, default_height, "Polly");
    SetTargetFPS(30);

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_H) || IsKeyPressed(KEY_A) ||
            IsKeyPressed(KEY_LEFT))
        {
            slide_index = max_i(0, slide_index - 1);
        }

        if (IsKeyPressed(KEY_L) || IsKeyPressed(KEY_D) ||
            IsKeyPressed(KEY_RIGHT))
        {
            slide_index = min_i(num_slides - 1, slide_index + 1);
        }

        RenderTexture2D texture =
            LoadRenderTexture(default_width, default_height);
        BeginDrawing();

        const int screen_width = GetScreenWidth();
        const int screen_height = GetScreenHeight();

        ClearBackground(RAYWHITE);

        BeginTextureMode(texture);

        DrawText("Congrats! You created your first window!", 190, 200, 20,
                 LIGHTGRAY);

        if (show_slide_number)
        {
            char buffer[10];
            if (sprintf(buffer, "%d/%d", slide_index, num_slides) < 0)
            {
                fprintf(stderr, "%s:%d -> sprintf failed for %d/%d", __FILE__,
                        __LINE__, slide_index, num_slides);
                exit(1);
            }

            const int font_size = 20;
            const Vector2 text_dimensions =
                MeasureTextEx(GetFontDefault(), buffer, font_size, 0);
            DrawText(buffer, default_width - 1.3 * text_dimensions.x,
                     default_height - 1.3 * text_dimensions.y, font_size, RED);
        }

        EndTextureMode();

        DrawTexturePro(
            texture.texture,
            (Rectangle){0, 0, (float)texture.texture.width,
                        (float)-texture.texture.height},
            (Rectangle){0, 0, (float)screen_width, (float)screen_height},
            (Vector2){0, 0}, 0.0f, WHITE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
