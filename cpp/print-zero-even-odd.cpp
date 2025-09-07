#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>

using std::condition_variable;
using std::function;
using std::mutex;
using std::unique_lock;

/// @class ZeroEvenOdd
/// @brief A class that ensures three methods (`zero`, `even`, and `odd`) are
/// executed in a specific, alternating sequence across different threads.
///
/// This solution uses a single `condition_variable` and a `mutex` to manage
/// the execution order based on a state represented by boolean flags. The
/// sequence is always: `zero` -> `odd` -> `zero` -> `even` -> `zero` -> `odd`,
/// and so on. The `zero` method always prints 0. The `odd` method prints odd
/// numbers, and the `even` method prints even numbers, up to `n`.
class ZeroEvenOdd {
 public:
  /// @brief Constructs a new ZeroEvenOdd object.
  /// @param n The total number of iterations for the sequence.
  ZeroEvenOdd(int n) {
    this->n = n;
    this->isZeroTime = true;
    this->isEvenTime = false;
  }

  /// @brief Prints `0` and then signals the next thread to proceed.
  ///
  /// This method is responsible for printing the number zero. It waits for its
  /// turn, prints `0`, and then updates the internal state to pass control
  /// to either the `odd` or `even` thread.
  /// @param printNumber A function that takes an `int` and prints it.
  void zero(function<void(int)> printNumber) {
    for (int i = 0; i < this->n; i++) {
      unique_lock lock(this->turnMutex);
      turnCV.wait(lock, [this]() { return this->isZeroTime; });

      printNumber(0);

      this->isZeroTime = false;

      this->turnCV.notify_all();
    }
  }

  /// @brief Prints even numbers and then signals the next thread to proceed.
  ///
  /// This method iterates through even numbers up to `n`. It waits for its turn
  /// (after a `zero` call), prints the current even number, and then passes
  /// control back to the `zero` thread.
  /// @param printNumber A function that takes an `int` and prints it.
  void even(function<void(int)> printNumber) {
    for (int i = 2; i <= this->n; i += 2) {
      unique_lock lock(this->turnMutex);
      turnCV.wait(lock,
                  [this]() { return !this->isZeroTime && this->isEvenTime; });

      printNumber(i);

      this->isEvenTime = false;
      this->isZeroTime = true;

      this->turnCV.notify_all();
    }
  }

  /// @brief Prints odd numbers and then signals the next thread to proceed.
  ///
  /// This method iterates through odd numbers up to `n`. It waits for its turn
  /// (after a `zero` call), prints the current odd number, and then passes
  /// control to the `even` thread for the next cycle.
  /// @param printNumber A function that takes an `int` and prints it.
  void odd(function<void(int)> printNumber) {
    for (int i = 1; i <= this->n; i += 2) {
      unique_lock lock(this->turnMutex);
      turnCV.wait(lock,
                  [this]() { return !this->isZeroTime && !this->isEvenTime; });

      printNumber(i);

      this->isEvenTime = true;
      this->isZeroTime = true;

      this->turnCV.notify_all();
    }
  }

 private:
  /// @brief The total number of iterations for the sequence.
  int n;
  /// @brief A boolean flag that indicates if it's the `zero` method's turn.
  bool isZeroTime;
  /// @brief A boolean flag that indicates if it's the `even` method's turn.
  bool isEvenTime;
  /// @brief The mutex used to protect the shared state (`isZeroTime` and
  /// `isEvenTime`) and the condition variable.
  mutex turnMutex;
  /// @brief The condition variable used to block and unblock threads based on
  /// whose turn it is.
  condition_variable turnCV;
};