#include <string>
#include <vector>

enum class CreditType {
  UNSET,
  CREDIT,
  WHITE_SPACE,
  END,
};

struct Credit {
  std::string message;
  int fontSize;

  // This is my X and here is Y - JanMarten_Jongerius
  float x;
  float y;
  bool final;
};

std::vector<Credit> ParseCredits(char *filePath, float offset);
