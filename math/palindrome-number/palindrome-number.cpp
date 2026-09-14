#include <algorithm>
#include <string>

class Solution {
 public:
  bool isPalindrome(int x) const {
    const std::string stringed = std::to_string(x);
    std::string reversed = stringed;
    std::reverse(reversed.begin(), reversed.end());

    return stringed == reversed;
  }
};