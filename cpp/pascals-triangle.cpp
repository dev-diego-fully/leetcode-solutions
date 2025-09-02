#include <vector>

using std::vector;

/// @brief A class to solve the Pascal's Triangle problem.
///
/// This class provides a method to generate the Pascal's Triangle up to a
/// specified number of rows.
class Solution {
 public:
  /// @brief Generates the Pascal's Triangle up to `numRows`.
  ///
  /// This public method serves as the entry point for the solution. It
  /// constructs the triangle row by row, starting with the base case of a
  /// single `1`.
  ///
  /// @param numRows The number of rows to generate.
  /// @return A vector of vectors representing the complete Pascal's Triangle.
  vector<vector<int>> generate(int numRows) const {
    vector<vector<int>> triangle(numRows);

    triangle[0] = (std::vector{1});

    for (int i = 1; i < numRows; i++) {
      triangle[i] = this->fromRow(triangle[i - 1]);
    }

    return triangle;
  }

 private:
  /// @brief Generates the next row of the triangle from the previous one.
  ///
  /// This private helper method calculates each element of the new row by
  /// summing adjacent elements from the previous row. It handles the edge
  /// cases by treating non-existent elements as zero.
  ///
  /// @param row A constant reference to the previous row of the triangle.
  /// @return A new vector of integers representing the next row.
  const vector<int> fromRow(const std::vector<int> &row) const {
    const std::size_t nextRowLen = row.size() + 1;

    vector<int> next(nextRowLen);

    for (std::size_t i = 0; i < nextRowLen; i++) {
      const int left = i == 0 ? 0 : row[i - 1];
      const int right = i >= nextRowLen - 1 ? 0 : row[i];

      next[i] = left + right;
    }

    return next;
  }
};