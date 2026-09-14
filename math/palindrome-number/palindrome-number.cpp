#include <string>

class Solution {
 public:
  bool isPalindrome(int x) const {
    const std::string stringed = std::to_string(x);
    const size_t limit = stringed.length() / 2;

    for (size_t i = 0; i < limit; i++) {
      const size_t j = stringed.length() - i - 1;

      if (stringed[i] != stringed[j]) {
        return false;
      }
    }

    return true;
  }
};