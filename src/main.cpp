/*******************************************************************************************
 *
 *   raylib [core] example - basic window
 *
 *   Example complexity rating: [★☆☆☆] 1/4
 *
 *   Welcome to raylib!
 *
 *   To test examples, just press F6 and execute 'raylib_compile_execute' script
 *   Note that compiled executable is placed in the same folder as .c file
 *
 *   To test the examples on Web, press F6 and execute
 * 'raylib_compile_execute_web' script Web version of the program is generated
 * in the same folder as .c file
 *
 *   You can find all basic examples on C:\raylib\raylib\examples folder or
 *   raylib official webpage: www.raylib.com
 *
 *   Enjoy using raylib. :)
 *
 *   Example originally created with raylib 1.0, last time updated with
 * raylib 1.0
 *
 *   Example licensed under an unmodified zlib/libpng license, which is an
 * OSI-certified, BSD-like license that allows static linking with closed source
 * software
 *
 *   Copyright (c) 2013-2025 Ramon Santamaria (@raysan5)
 *
 ********************************************************************************************/

#include "cred_file_parser.hpp"
#include "raylib.h"
#include <vector>

#define DEADFF CLITERAL(Color){0xde, 0xad, 0xff, 0xff}

#define WINDOW_HEIGHT 1080
#define WINDOW_WIDTH 1920

int main(void) {
  // Enable transparency flag *before* InitWindow
  SetConfigFlags(FLAG_WINDOW_TRANSPARENT);
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "just-roll-credits");
  SetTargetFPS(60);

  // Set your desired background color with alpha (e.g., clear to transparent)
  Color transparentColor = {0, 0, 0, 0}; // Black with full transparency

  // I want to get my new font in here, also color
  // Parse credits from some formatted file
  // Load credits into data structure that informs game loop how to deal with
  // each element Update the position
  std::vector<Credit> credits = ParseCredits(WINDOW_HEIGHT, WINDOW_WIDTH);
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(transparentColor); // Clears to fully transparent

    for (Credit &credit : credits) {
      DrawText(credit.message.c_str(), credit.x, credit.y, credit.fontSize,
               Fade(DEADFF, 0.9f));

      credit.y = credit.y - 1;
    }

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
