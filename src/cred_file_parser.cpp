#include "cred_file_parser.hpp"
#include "raylib.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

// Create a static map to store the string-to-enum mapping
static const std::unordered_map<std::string, CreditType> creditTypeMap = {
    {"CREDIT", CreditType::CREDIT}, {"WHITE_SPACE", CreditType::WHITE_SPACE}};

std::vector<Credit> ParseCredits(int offset, int windowWidth) {
  int screenHorizontalCenter = windowWidth / 2;
  Font font = LoadFontEx(
      "/home/jane/just-stream/just-roll-credits/assets/font.ttf", 64, NULL, 0);
  std::string filename = "/home/jane/just-stream/just-roll-credits/"
                         "assets/captions.whatever";

  std::ifstream inputFile(filename); // Open the file directly using constructor
  std::string line;
  std::vector<Credit> credits;

  if (!inputFile.is_open()) {
    std::cerr << "Error opening file: " << filename << std::endl;
    throw std::invalid_argument("something has exploded, oh no!");
  }

  // Read the file line by line
  while (std::getline(inputFile, line)) {
    if (line.empty() || line[0] == '#') {
      continue;
    }

    std::stringstream ss(line); // Create a stringstream from the line
    std::string lineType;

    std::getline(ss, lineType, ',');

    CreditType t = creditTypeMap.at(lineType);
    Credit credit;

    switch (t) {
    case CreditType::CREDIT: {
      std::string message;
      std::getline(ss, message, ',');

      std::string fontSizeString;
      std::getline(ss, fontSizeString, ',');
      int fontSize = std::stoi(fontSizeString);

      Vector2 textSize = MeasureTextEx(font, message.c_str(), fontSize, 2.0f);

      int the_x = (screenHorizontalCenter) - (int)textSize.x / 2;
      Credit credit = {.message = message,
                       .fontSize = fontSize,
                       .height = (int)textSize.y,
                       .width = (int)textSize.x,
                       .x = the_x};

      credit.y = offset;
      offset += (int)textSize.y + 10;
      credits.push_back(credit);
      break;
    }
    case CreditType::WHITE_SPACE: {
      std::string amountOfSpace;
      std::getline(ss, amountOfSpace, ',');
      int space = std::stoi(amountOfSpace);
      offset += space;
      break;
    }
    case CreditType::UNSET:
    default:
      std::cout << "erm what the glerm" << std::endl;
      break;
    }
  }

  inputFile.close();

  return credits;
}
