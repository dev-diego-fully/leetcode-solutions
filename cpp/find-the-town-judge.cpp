#include <set>
#include <vector>

using std::set;
using std::vector;

/// @class Solution
/// @brief A class that provides a solution to the "Find the Town Judge"
/// problem.
///
/// The problem involves identifying a single person in a town who meets two
/// specific criteria: they trust no one, and everyone else trusts them.
class Solution {
 public:
  /// @brief Finds the Town Judge from a list of trust relationships.
  ///
  /// This method iterates through the trust relationships to first identify
  /// all individuals who trust someone else and to count how many people trust
  /// each individual. It then checks each person against the two criteria
  /// for being the Judge.
  ///
  /// The Judge is defined as the person who:
  /// 1. Trusts nobody.
  /// 2. Is trusted by exactly `n - 1` other people.
  ///
  /// @param n The total number of people in the town, labeled from 1 to `n`.
  /// @param trust A vector of vectors where each inner vector `[a, b]`
  /// indicates that person `a` trusts person `b`.
  /// @return The label of the Town Judge if one exists, otherwise returns -1.
  int findJudge(int n, vector<vector<int>>& trust) {
    set<int> trustInSomeOne;
    vector<int> isTrustedBy(n, 0);

    for (auto current = trust.begin(); current != trust.end(); current++) {
      const int truster = current->at(0);
      const int trusted = current->at(1);

      trustInSomeOne.insert(truster);
      isTrustedBy[trusted - 1]++;
    }

    for (int i = 0; i < n; i++) {
      const int person = i + 1;

      if (trustInSomeOne.find(person) == trustInSomeOne.end() &&
          isTrustedBy.at(i) == n - 1) {
        return person;
      }
    }

    return -1;
  }
};