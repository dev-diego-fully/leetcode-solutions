#include <map>
#include <string>
#include <utility>

using std::make_pair;
using std::map;
using std::string;

/**
 * @brief Solution for converting Roman numerals to integers.
 */
class Solution {
 public:
  /**
   * @brief Converts a Roman numeral string to its corresponding integer value.
   *
   * @param s The Roman numeral string to convert.
   * @return The integer representation of the Roman numeral.
   */
  int romanToInt(string s) const {
    const size_t len = s.length();

    int value = 0;

    for (size_t i = 0; i < len; i++) {
      const char current = s.at(i);

      if (i + 1 < len) {
        const char next = s.at(i + 1);
        const string multiTokenCandidate = string{current, next};

        if (this->isValidMultiToken(multiTokenCandidate)) {
          value += this->getMultiTokenValue(multiTokenCandidate);
          i++;
          continue;
        }
      }

      value += this->getSingleTokenValue(current);
    }

    return value;
  }

 private:
  /**
   * @brief Map storing two-character subtractive Roman numeral combinations and
   * their values.
   */
  map<string, int> multiTokenValues{
      make_pair(string("IV"), 4),   make_pair(string("IX"), 9),
      make_pair(string("XL"), 40),  make_pair(string("XC"), 90),
      make_pair(string("CD"), 400), make_pair("CM", 900)};

  /**
   * @brief Map storing single Roman numeral characters and their values.
   */
  map<char, int> singleTokenValues{make_pair('I', 1),   make_pair('V', 5),
                                   make_pair('X', 10),  make_pair('L', 50),
                                   make_pair('C', 100), make_pair('D', 500),
                                   make_pair('M', 1000)};

  /**
   * @brief Checks if a two-character string is a valid subtractive Roman
   * numeral combination.
   *
   * @param candidate The string candidate to validate.
   * @return True if the candidate is in the multiTokenValues map, false
   * otherwise.
   */
  bool isValidMultiToken(const string& candidate) const {
    return this->multiTokenValues.find(candidate) !=
           this->multiTokenValues.end();
  }

  /**
   * @brief Retrieves the integer value for a valid two-character Roman numeral
   * combination.
   *
   * @param token The two-character Roman numeral combination.
   * @return The integer value associated with the token.
   */
  int getMultiTokenValue(const string& token) const {
    return this->multiTokenValues.at(token);
  }

  /**
   * @brief Retrieves the integer value for a single Roman numeral character.
   *
   * @param token The Roman numeral character.
   * @return The integer value associated with the token.
   */
  int getSingleTokenValue(char token) const {
    return this->singleTokenValues.at(token);
  }
};