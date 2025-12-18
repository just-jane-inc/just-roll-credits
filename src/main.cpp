#include "cred_file_parser.hpp"
#include "raylib.h"
#include <vector>

#define DEADFF CLITERAL(Color){0xde, 0xad, 0xff, 0xff}

#define WINDOW_HEIGHT 1080
#define WINDOW_WIDTH 1920

int main(void) {
  // Enable transparency flag *before* InitWindow
  SetConfigFlags(FLAG_WINDOW_TRANSPARENT);

  Font font = LoadFontEx(
      "/home/jane/just-stream/just-roll-credits/assets/font.ttf", 64, NULL, 0);

  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "just-roll-credits");
  SetTargetFPS(60);

  Color transparentColor = {0, 0, 0, 0};

  // I want to get my new font in here, also color
  // Parse credits from some formatted file
  // Load credits into data structure that informs game loop how to deal with
  // each element Update the position
  std::vector<Credit> credits = ParseCredits(WINDOW_HEIGHT, WINDOW_WIDTH);
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(transparentColor);

    for (Credit &credit : credits) {
      Vector2 position = {(float)credit.x, (float)credit.y};
      DrawTextEx(font, credit.message.c_str(), position, credit.fontSize, 2.0f,
                 DEADFF);

      credit.y--;
    }

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
