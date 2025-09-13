#include <vector>

using std::vector;

/// @class Solution
/// @brief A class that provides a solution to the "Find Center of Star Graph"
/// problem.
///
/// A star graph is a specific type of graph where one central node is connected
/// to all other nodes, and there are no other connections. The solution
/// leverages a key property of this graph structure: the center node is the
/// only node with a degree (number of connections) equal to `n - 1`, where `n`
/// is the total number of nodes.
class Solution {
 public:
  /// @brief Finds the center of a star graph.
  ///
  /// The method determines the number of connections for each node. In a star
  /// graph, the central node will have a degree equal to `n - 1` (where `n` is
  /// the number of nodes), while all other nodes will have a degree of 1. The
  /// algorithm finds the node that satisfies this condition.
  ///
  /// @param edges A vector of vectors, where each inner vector represents an
  /// edge `[u, v]` connecting node `u` and `v`.
  /// @return The label of the center node. If no such node is found, returns
  /// -1.
  int findCenter(vector<vector<int>>& edges) {
    const int n = edges.size() + 1;
    vector<int> connectionsCount(n + 1, 0);

    for (auto edge = edges.begin(); edge != edges.end(); edge++) {
      const int left = edge->at(0);
      const int right = edge->at(1);

      connectionsCount[left]++;
      connectionsCount[right]++;
    }

    for (int i = 1; i <= n; i++) {
      if (connectionsCount[i] == n - 1) {
        return i;
      }
    }

    return -1;
  }
};