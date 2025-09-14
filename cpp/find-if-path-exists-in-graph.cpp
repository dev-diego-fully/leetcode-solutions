#include <queue>
#include <unordered_set>
#include <vector>

using std::queue;
using std::unordered_set;
using std::vector;

/// @brief A type alias for a graph's adjacency list representation.
///
/// The graph is represented as a vector where each index corresponds to a node,
/// and the value is an `unordered_set` containing its neighbors.
using AdjanceList = vector<unordered_set<int>>;

/// @class Solution
/// @brief A class that provides a solution to the "Find if Path Exists in
/// Graph" problem.
///
/// This solution uses a Breadth-First Search (BFS) algorithm to efficiently
/// traverse the graph and determine if a path exists from the source to the
/// destination.
class Solution {
 public:
  /// @brief Determines if a valid path exists between two nodes in a graph.
  ///
  /// The method performs a BFS starting from the `source` node. It explores
  /// the graph layer by layer, checking if the `destination` node is reachable.
  ///
  /// @param n The number of nodes in the graph.
  /// @param edges A constant reference to a vector of edges, where each edge is
  /// a pair of connected nodes.
  /// @param source The starting node of the path.
  /// @param destination The target node of the path.
  /// @return `true` if a path exists from source to destination, `false`
  /// otherwise.
  bool validPath(int n, const vector<vector<int>>& edges, int source,
                 int destination) const {
    AdjanceList adjanceList = this->toAdjanceList(n, edges);

    unordered_set<int> seens;
    queue<int> toVisit({source});

    while (!toVisit.empty()) {
      int current = toVisit.front();
      toVisit.pop();

      if (current == destination) {
        return true;
      }

      seens.insert(current);

      for (auto node : adjanceList[current]) {
        if (!this->setContains(seens, node)) {
          seens.insert(node);
          toVisit.push(node);
        }
      }
    }

    return false;
  }

 private:
  /// @brief Converts a list of edges into an adjacency list representation of
  /// the graph.
  ///
  /// The adjacency list is a more suitable data structure for graph traversal
  /// algorithms like BFS. It represents the graph as a collection of lists,
  /// where each list contains the neighbors of a specific node.
  ///
  /// @param n The number of nodes in the graph.
  /// @param edges A constant reference to the vector of edges.
  /// @return An adjacency list representing the graph.
  AdjanceList toAdjanceList(int n, const vector<vector<int>>& edges) const {
    AdjanceList adjanceList(n);

    for (auto edge : edges) {
      const int left = edge.at(0);
      const int right = edge.at(1);

      adjanceList[left].insert(right);
      adjanceList[right].insert(left);
    }

    return adjanceList;
  }

  /// @brief Checks if an element exists within an `unordered_set`.
  ///
  /// This is a helper function to provide clarity to the main algorithm.
  /// @tparam T The type of the elements in the set.
  /// @param st The `unordered_set` to search within.
  /// @param element The element to find.
  /// @return `true` if the element is in the set, `false` otherwise.
  template <typename T>
  bool setContains(const unordered_set<T>& st, T element) const {
    return st.find(element) != st.end();
  }
};