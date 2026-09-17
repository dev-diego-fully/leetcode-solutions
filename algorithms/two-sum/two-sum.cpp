#include <vector>

using std::vector;

/**
 * @brief Solution for the Two Sum problem.
 */
class Solution {
 public:
  /**
   * @brief Finds the indices of two numbers that add up to the target sum.
   *
   * @param nums Vector of integers.
   * @param target Target value to reach.
   * @return Vector containing the two 0-based indices, or {-1, -1} if no
   * solution exists.
   */
  vector<int> twoSum(const vector<int>& nums, int target) const {
    for (size_t i = 0; i < nums.size() - 1; i++) {
      for (size_t j = i + 1; j < nums.size(); j++) {
        if (nums[i] + nums[j] == target) {
          return {static_cast<int>(i), static_cast<int>(j)};
        }
      }
    }

    return {-1, -1};
  }
};