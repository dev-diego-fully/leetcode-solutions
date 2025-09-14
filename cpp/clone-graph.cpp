#include <map>
#include <stack>
#include <tuple>
#include <unordered_set>
#include <vector>

using std::map;
using std::stack;
using std::tuple;
using std::unordered_set;
using std::vector;

/// @class Solution
/// @brief A class that provides a solution for cloning an undirected graph.
///
/// This solution uses a two-pass approach. The first pass traverses the original graph
/// to collect all nodes, and the second pass creates deep copies of the nodes and
/// establishes the correct relationships between them.
class Solution {
 public:
  /// @brief Creates a deep copy of a given undirected graph.
  ///
  /// The method first traverses the graph starting from the provided `node` to discover all
  /// reachable nodes. It then creates new copies of each node, and finally, it links
  /// the copies' neighbors to correctly reflect the original graph's structure.
  ///
  /// @param node The starting node of the graph to be cloned.
  /// @return A pointer to the copied starting node, or `nullptr` if the input is `nullptr`.
  Node* cloneGraph(Node* node) const {
    if (node == nullptr) {
      return nullptr;
    }
    
    unordered_set<Node*> nodes = this->listNodes(node);
    map<Node*, Node*> copies = this->copyNodes(nodes);

    return copies.at(node);
  }

 private:
  /// @brief Traverses the graph using Depth-First Search (DFS) to find all nodes.
  ///
  /// It uses a stack to perform an iterative DFS and an `unordered_set` to keep
  /// track of visited nodes, preventing infinite loops in graphs with cycles.
  /// @param head The starting node for the traversal.
  /// @return A set containing pointers to all nodes in the graph.
  unordered_set<Node*> listNodes(Node* head) const {
    unordered_set<Node*> nodes;
    stack<Node*> nexts({head});

    while (!nexts.empty()) {
      Node* current = nexts.top();
      nexts.pop();

      if (!this->setContains(nodes, current)) {
        nodes.insert(current);

        for (Node* neighbor : current->neighbors) {
          if (!this->setContains(nodes, neighbor)) {
            nexts.push(neighbor);
          }
        }
      }
    }

    return nodes;
  }

  /// @brief Creates deep copies of a set of nodes and their neighbors.
  ///
  /// This function is the second pass of the cloning process. It first creates
  /// a new `Node` instance for each node in the provided set. It then iterates
  /// again to establish the neighbor connections for each new copy.
  /// @param nodes A constant reference to the set of original nodes.
  /// @return A map that links each original node pointer to its new copy's pointer.
  map<Node*, Node*> copyNodes(const unordered_set<Node*>& nodes) const {
    map<Node*, Node*> copies;

    for (Node* node : nodes) {
      copies[node] = new Node(node->val);
    }

    for (Node* node : nodes) {
      Node* copy = copies[node];

      for (Node* neighbor : node->neighbors) {
        copy->neighbors.push_back(copies[neighbor]);
      }
    }

    return copies;
  }

  /// @brief A helper function to check if a set contains a specific node.
  /// @param set A constant reference to the set to be searched.
  /// @param node The node pointer to look for.
  /// @return `true` if the node is in the set, `false` otherwise.
  bool setContains(const unordered_set<Node*>& set, Node* node) const {
    return set.find(node) != set.end();
  }
};