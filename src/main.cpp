#include "cred_file_parser.hpp"
#include "raylib.h"
#include <vector>

#define DEADFF CLITERAL(Color){0xde, 0xad, 0xff, 0xff}
#define TRANSPARENT CLITERAL(Color){0x00, 0x00, 0x00, 0x00}

#define WINDOW_HEIGHT 1080.0
#define WINDOW_WIDTH 1920.0

int main(void) {
  // Enable transparency flag *before* InitWindow
  SetConfigFlags(FLAG_WINDOW_TRANSPARENT);

  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "just-roll-credits");

  // we must load font after init window
  Font font = LoadFont("assets/font.ttf");
  SetTargetFPS(60);

  std::vector<Credit> credits = ParseCredits(GetScreenHeight());

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(TRANSPARENT);

    float spacing = 2.0f;
    float centerX = GetScreenWidth() * 0.5f;

    for (Credit &credit : credits) {
      Vector2 textSize = MeasureTextEx(font, credit.message.c_str(), credit.fontSize, spacing);

      DrawTextPro(font,
                  credit.message.c_str(),
                  {centerX, credit.y},
                  {textSize.x * 0.5f, 0.0f},
                  0.0f,
                  credit.fontSize,
                  spacing,
                  DEADFF);

      credit.y--;
    }

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
