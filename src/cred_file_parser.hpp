#include <string>
#include <vector>

enum class CreditType { UNSET, CREDIT, WHITE_SPACE, PAUSE, GRID, FADE_IN };

// !click - Red_Epicness
struct Credit {
  std::string message;
  int fontSize;

  // This is my X and here is Y - JanMarten_Jongerius
  float x;
  float y;
  CreditType creditType;
  bool removeCredit;
  int keepFor;
};

std::vector<Credit> ParseCredits(char *filePath, float offset);
Credit ParseGridCredit(std::stringstream &line, float offset);
