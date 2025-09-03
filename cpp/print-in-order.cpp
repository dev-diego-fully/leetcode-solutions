/// @brief Defines the Foo class for sequential method execution.

#include <condition_variable>
#include <functional>
#include <mutex>

using std::condition_variable;
using std::function;
using std::mutex;
using std::unique_lock;

/// @brief A class that ensures three methods are executed in a specific order:
/// first(), then second(), then third().
///
/// This implementation uses a single condition variable and a shared turn counter
/// to manage the execution order of the three methods. A mutex protects the
/// turn counter, while the condition variable allows threads to wait for their
/// specific turn before proceeding.
class Foo {
 public:
  /// @brief Constructs a new Foo object and initializes the turn counter.
  Foo() {
    this->turn = 0;
  }

  /// @brief Executes the first step of the sequence.
  ///
  /// This method waits until `turn` is 0, executes its action, increments the
  /// turn counter, and notifies all waiting threads.
  /// @param printFirst A callable object that performs the action for the first step.
  void first(function<void()> printFirst) {
    unique_lock lock(this->turnMtx);
    this->turnCV.wait(lock, [this]() { return this->turn == 0; });

    printFirst();

    this->turn += 1;
    this->turnCV.notify_all();
  }

  /// @brief Executes the second step of the sequence.
  ///
  /// This method waits until `turn` is 1, executes its action, increments the
  /// turn counter, and notifies all waiting threads.
  /// @param printSecond A callable object that performs the action for the second step.
  void second(function<void()> printSecond) {
    unique_lock<mutex> lock(this->turnMtx);
    this->turnCV.wait(lock, [this]() { return this->turn == 1; });

    printSecond();

    this->turn += 1;
    this->turnCV.notify_all();
  }

  /// @brief Executes the third and final step of the sequence.
  ///
  /// This method waits until `turn` is 2, executes its action, and then
  /// concludes the sequence.
  /// @param printThird A callable object that performs the action for the third step.
  void third(function<void()> printThird) {
    unique_lock<mutex> lock(this->turnMtx);
    this->turnCV.wait(lock, [this]() { return this->turn == 2; });

    printThird();
  }

 private:
  /// @brief An integer counter that indicates which step is currently active.
  uint8_t turn;
  /// @brief The condition variable used to block and unblock threads based on the `turn` counter.
  condition_variable turnCV;
  /// @brief The mutex used to protect the `turn` counter and the condition variable.
  mutex turnMtx;
};