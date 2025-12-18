#include "cred_file_parser.hpp"
#include "raylib.h"
#include <iostream>
#include <vector>

#define DEADFF CLITERAL(Color){0xde, 0xad, 0xff, 0xff}
#define TRANSPARENT CLITERAL(Color){0x00, 0x00, 0x00, 0x00}

#define WINDOW_HEIGHT 1080.0
#define WINDOW_WIDTH 1920.0

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "program requires exectly one argument, a file path to the "
                 "captions file"
              << std::endl;

    return 1;
  }

  char *creditsFilePath = argv[1];

  // Enable transparency flag *before* InitWindow
  SetConfigFlags(FLAG_WINDOW_TRANSPARENT);

  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "just-roll-credits");

  // we must load font after init window
  Font font = LoadFont("assets/font.ttf");
  SetTargetFPS(60);

  std::vector<Credit> credits =
      ParseCredits(creditsFilePath, GetScreenHeight());
  bool keepRolling = true;

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(TRANSPARENT);

    float spacing = 2.0f;
    float centerX = GetScreenWidth() * 0.5f;

    for (Credit &credit : credits) {

      Vector2 textSize =
          MeasureTextEx(font, credit.message.c_str(), credit.fontSize, spacing);

      DrawTextPro(font, credit.message.c_str(), {centerX, credit.y},
                  {textSize.x * 0.5f, 0.0f}, 0.0f, credit.fontSize, spacing,
                  DEADFF);

      if (keepRolling) {
        credit.y--;
        if (credit.final && credit.y <= GetScreenHeight() / 2.0f) {
          keepRolling = false;
        }
      }
    }

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
