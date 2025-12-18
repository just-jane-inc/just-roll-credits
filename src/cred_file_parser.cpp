#include "cred_file_parser.hpp"
#include "raylib.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <unordered_map>
#include <vector>

static const std::unordered_map<std::string, CreditType> creditTypeMap = {
    {"CREDIT", CreditType::CREDIT},
    {"WHITE_SPACE", CreditType::WHITE_SPACE},
    {"END", CreditType::END}};

std::vector<Credit> ParseCredits(char *captionsPath, float offset) {
  Font font = LoadFont("assets/font.ttf");

  std::ifstream inputFile(captionsPath);
  std::string line;
  std::vector<Credit> credits;

  if (!inputFile.is_open()) {
    std::cerr << "err opening file: " << captionsPath << std::endl;
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

      Credit credit = {.message = message,
                       .fontSize = fontSize,
                       .y = offset,
                       .final = false};

      Vector2 textSize = MeasureTextEx(font, message.c_str(), fontSize, 2.0f);
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
    case CreditType::END: {
      credits.push_back({.y = offset, .final = true});
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
