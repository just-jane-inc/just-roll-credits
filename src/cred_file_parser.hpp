#include <string>
#include <vector>

enum class CreditType {
  UNSET,
  CREDIT,
  WHITE_SPACE,
};

struct Credit {
  std::string message;
  int fontSize;
  int height;
  int width;
  int x;
  int y;
};

std::vector<Credit> ParseCredits(int offset, int windowWidth);
