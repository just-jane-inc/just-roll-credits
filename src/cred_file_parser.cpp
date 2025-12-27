#include "cred_file_parser.hpp"
#include "raylib.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <unordered_map>
#include <vector>

static const std::unordered_map<std::string, CreditType> creditTypeMap = {
    {"CREDIT", CreditType::CREDIT},
    {"WHITE_SPACE", CreditType::WHITE_SPACE},
    {"PAUSE", CreditType::PAUSE},
    {"GRID", CreditType::GRID},
    {"FADE_IN", CreditType::FADE_IN}};

// I'm the best foxgirl - Red_Epicness
std::vector<Credit> ParseCredits(char *captionsPath, float offset) {
  Font font =
      LoadFont("/home/jane/just-stream/just-roll-credits/assets/font.ttf");

  std::ifstream inputFile(captionsPath);
  std::string line;
  std::vector<Credit> credits;

  if (!inputFile.is_open()) {
    std::cerr << "err opening file: " << captionsPath << std::endl;
    throw std::invalid_argument("something has exploded, oh no!");
  }

  // Read the file line by line
  int count = 0;
  while (std::getline(inputFile, line)) {
    if (line.empty() || line[0] == '#') {
      continue;
    }

    std::stringstream ss(line);
    std::string lineType;

    std::getline(ss, lineType, ',');

    CreditType t = creditTypeMap.at(lineType);
    Credit credit;

    switch (t) {
    case CreditType::FADE_IN: {
      std::string time;
      std::getline(ss, time, ',');
      int frameCount = std::stoi(time);

      std::string message;
      std::getline(ss, message, ',');

      std::string fontSizeString;
      std::getline(ss, fontSizeString, ',');
      int fontSize = std::stoi(fontSizeString);

      Credit credit = {.message = message,
                       .fontSize = fontSize,
                       .y = offset,
                       .creditType = t,
                       .keepFor = frameCount};

      Vector2 textSize = MeasureTextEx(font, message.c_str(), fontSize, 2.0f);
      offset += (int)textSize.y + 10;
      credits.push_back(credit);
      break;
    }
    case CreditType::CREDIT: {
      std::string message;
      std::getline(ss, message, ',');

      std::string fontSizeString;
      std::getline(ss, fontSizeString, ',');
      int fontSize = std::stoi(fontSizeString);

      Credit credit = {.message = message,
                       .fontSize = fontSize,
                       .y = offset,
                       .creditType = t};

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
    case CreditType::GRID: {
      Credit credit = ParseGridCredit(ss, offset);
      Vector2 textSize =
          MeasureTextEx(font, credit.message.c_str(), credit.fontSize, 2.0f);
      offset += (int)textSize.y + 10;
      credits.push_back(credit);
      break;
    }
    case CreditType::PAUSE: {
      std::string size;
      std::getline(ss, size, ',');

      // we use fontSize here as a stupid hack to encode the length of a pause
      // because i don't want to make this simple struct any weirder right now.
      // foxgirls best girls - Red_Epicness
      int space = std::stoi(size);
      Credit credit = {.fontSize = space, .y = offset, .creditType = t};
      credits.push_back(credit);
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

Credit ParseGridCredit(std::stringstream &line, float offset) {
  // used to remove trailing whitespace from the right-most column
  // to help center the grid
  // meow - Red_Epicness
  auto rtrim_in_place = [](std::string &s) {
    while (!s.empty()) {
      char c = s.back();
      if (c == ' ' || c == '\t' || c == '\r')
        s.pop_back();
      else
        break;
    }
  };

  std::string numberOfColumns;
  std::getline(line, numberOfColumns, ',');
  int columns = std::stoi(numberOfColumns);

  std::string fontSize;
  std::getline(line, fontSize, ',');
  int fSize = std::stoi(fontSize);

  std::string curr;
  std::vector<std::string> creditsDifferentName;
  while (std::getline(line, curr, ',')) {
    creditsDifferentName.push_back(curr);
  }

  std::stringstream out;
  std::string row;
  row.reserve(256);

  int count = 0;
  for (const std::string &credit : creditsDifferentName) {
    if (count != 0 && (count % columns) == 0) {
      rtrim_in_place(row);
      out << row << '\n';
      row.clear();
    }

    std::ostringstream cell;
    cell << std::left << std::setw(25) << credit;
    row += cell.str();

    count += 1;
  }

  rtrim_in_place(row);
  out << row;

  Credit credit = {
      .message = out.str(),
      .fontSize = fSize,
      .y = offset,
      .creditType = CreditType::GRID,
  };

  return credit;
}
