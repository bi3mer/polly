#include "stdio.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "general.h"
#include "raylib.h"

typedef struct
{
    Color background;
    Color title;
    Color text;
    int title_size;
    int text_size;
    int slide_number_size;
    bool show_slide_numbers;
} Theme;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./polly [path-to-slides.md].\n");
        exit(0);
    }

    // How to open a website on MacOS. Will use for hyperlinks.
    // system("open https://bi3mer.github.io");

    ///////////////////////////////////////////////////////////////////////////
    // set up defaults
    Theme theme = {
        .background = BLACK,
        .title = ORANGE,
        .text = RAYWHITE,
        .title_size = 40,
        .text_size = 30,
        .slide_number_size = 20,
        .show_slide_numbers = true,
    };

    ///////////////////////////////////////////////////////////////////////////
    // Read in the markdown file
    // [ ] header at top of markdown file should be able to update the theme
    // [ ] header should be able to update font sizes

    ///////////////////////////////////////////////////////////////////////////
    // Start raylib application
    int slide_index = 0; // temp
    int num_slides = 30; // temp
    bool show_cursor = true;
    bool show_help = false;

    const int default_width = 1080;
    const int default_height = 720;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(default_width, default_height, "Polly");
    SetTargetFPS(30);

    while (!WindowShouldClose())
    {
        /////////// Handle Key Presses ///////////
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

        if (IsKeyPressed(KEY_H))
        {
            show_help = !show_help;
        }

        if (IsKeyPressed(KEY_S))
        {
            // @BUG: doesn't seem to work on MacOS
            show_cursor = !show_cursor;
            if (show_cursor)
                ShowCursor();
            else
                HideCursor();
        }

        /////////// set up for drawing ///////////
        RenderTexture2D texture =
            LoadRenderTexture(default_width, default_height);
        BeginDrawing();

        const int screen_width = GetScreenWidth();
        const int screen_height = GetScreenHeight();

        ClearBackground(theme.background);

        BeginTextureMode(texture);

        DrawText("Congrats! You created your first window!", 190, 200,
                 theme.text_size, LIGHTGRAY);

        /////////// slide numbers ///////////
        if (theme.show_slide_numbers)
        {
            char buffer[10];
            if (sprintf(buffer, "%d/%d", slide_index, num_slides) < 0)
            {
                fprintf(stderr, "%s:%d -> sprintf failed for %d/%d", __FILE__,
                        __LINE__, slide_index, num_slides);
                exit(1);
            }

            const Vector2 text_dimensions = MeasureTextEx(
                GetFontDefault(), buffer, theme.slide_number_size, 0);
            DrawText(buffer, default_width - 1.3 * text_dimensions.x,
                     default_height - 1.3 * text_dimensions.y,
                     theme.slide_number_size, theme.text);
        }

        /////////// help menu ///////////
        if (show_help)
        {
            const int help_title_size = 30;
            const int help_font_size = 25;
            const Vector2 top_left = {.x = 0.1 * default_width,
                                      .y = 0.1 * default_height};
            const Vector2 dimensions = {
                .x = default_width * 0.8,
                .y = default_height * 0.8,
            };

            DrawRectangleV(top_left, dimensions, LIGHTGRAY);

            // title
            const int tile_width = MeasureText("Help Menu", help_font_size);
            DrawText("Help Menu",
                     top_left.x + dimensions.x / 2 - tile_width / 2,
                     top_left.x - 20, help_title_size, RED);

            // general directions
            int y_mod = 80;
            DrawText("- A, H, or left arrow to go left", top_left.x + 10,
                     top_left.y + y_mod, help_font_size, RED);

            y_mod += 30;
            DrawText("- D, L, or right arrow to go right", top_left.x + 10,
                     top_left.y + y_mod, help_font_size, RED);

            y_mod += 30;
            DrawText("- H to show the help menu (this)", top_left.x + 10,
                     top_left.y + y_mod, help_font_size, RED);

            y_mod += 30;
            DrawText("- S to show laser pointer", top_left.x + 10,
                     top_left.y + y_mod, help_font_size, RED);
        }

        /////////// red laser cursor ///////////
        if (!show_cursor)
        {
            Vector2 mouse = GetMousePosition();
            mouse.x = (mouse.x / screen_width) * default_width;
            mouse.y = (mouse.y / screen_height) * default_height;

            DrawCircle(mouse.x, mouse.y, 5, RED);
        }

        /////////// finish drawing ///////////
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
