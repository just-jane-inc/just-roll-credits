#include "cred_file_parser.hpp"
#include "raylib.h"
#include <cstdint>
#include <iostream>
#include <vector>

#define DEADFF CLITERAL(Color){0xde, 0xad, 0xff, 0xff}
#define TRANSPARENT CLITERAL(Color){0x00, 0x00, 0x00, 0x00}

#define WINDOW_HEIGHT 1080.0
#define WINDOW_WIDTH 1920.0

// You look great today! - Red_Epicness
int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "program requires exectly one argument, a file path to the "
                 "captions file"
              << std::endl;

    return 1;
  }

  char *creditsFilePath = argv[1];

  // Enable flags *before* InitWindow
  SetConfigFlags(FLAG_WINDOW_TRANSPARENT | FLAG_WINDOW_ALWAYS_RUN);
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "just-roll-credits");

  // we must load font after init window
  Font font =
      LoadFont("/home/jane/just-stream/just-roll-credits/assets/font.ttf");
  SetTargetFPS(60);

  std::vector<Credit> credits =
      ParseCredits(creditsFilePath, GetScreenHeight());
  int pause = 0;
  int fadeIn = -1;
  int fadeOut = -1;

  Color deadff = Color{0xde, 0xad, 0xff, 0x00};

  while (!WindowShouldClose()) {

    BeginDrawing();
    ClearBackground(TRANSPARENT);

    float spacing = 2.0f;
    float centerX = GetScreenWidth() * 0.5f;

    while (!credits.empty() && credits[0].removeCredit) {
      credits.erase(credits.begin());
    }

    if (credits.empty()) {
      break;
    }

    if (credits[0].creditType == CreditType::FADE_IN) {
      Credit *credit = &credits[0];

      if (fadeIn == -1) {
        fadeIn = 1;
        fadeOut = 1;
        deadff.a = 0;
      }

      if (fadeIn == 1) {
        deadff.a += 5;
        if (deadff.a == 0xff) {
          fadeIn = 0;
        }

      } else if (credit->keepFor > 0) {
        credit->keepFor -= 1;
        deadff.a = 0xff;
      } else if (fadeOut == 1) {
        deadff.a -= 5;
        if (deadff.a == 0x00) {
          fadeOut = 0;
        }
      } else {
        credit->removeCredit = true;
        fadeIn = -1;
        fadeOut = -1;
      }

      Vector2 textSize = MeasureTextEx(font, credit->message.c_str(),
                                       credit->fontSize, spacing);

      DrawTextPro(
          font, credit->message.c_str(), {centerX, GetScreenHeight() / 2.0f},
          {textSize.x * 0.5f, 0.0f}, 0.0f, credit->fontSize, spacing, deadff);

      EndDrawing();
      continue;
    }

    for (Credit &credit : credits) {
      Vector2 textSize =
          MeasureTextEx(font, credit.message.c_str(), credit.fontSize, spacing);

      credit.removeCredit = (credit.y + textSize.y) < 0;

      switch (credit.creditType) {
      case CreditType::PAUSE:
        if (credit.y == (GetScreenHeight() / 2.0f)) {
          pause = credit.fontSize;
          credit.y = 0;
        }
        break;
      case CreditType::FADE_IN:
        break;
      default:
        DrawTextPro(font, credit.message.c_str(), {centerX, credit.y},
                    {textSize.x * 0.5f, 0.0f}, 0.0f, credit.fontSize, spacing,
                    DEADFF);
        break;
      }

      if (pause <= 0) {
        credit.y--;
      }
    }

    if (pause > 0) {
      pause = pause - 1;
    }

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
