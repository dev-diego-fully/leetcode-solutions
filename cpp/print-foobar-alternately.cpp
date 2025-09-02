#include <condition_variable>
#include <functional>
#include <mutex>

using std::condition_variable;
using std::function;
using std::mutex;
using std::unique_lock;

/// @class FooBar
/// @brief A class that orchestrates the alternating execution of two methods, `foo` and `bar`, from separate threads.
///
/// The class ensures a strict sequence where `foo` runs, then `bar` runs, then `foo` again,
/// and so on, for a specified number of iterations. This is achieved using a condition variable
/// and a mutex to signal and wait for the correct turn.
class FooBar {
 private:
  /// @brief The total number of times `foo` and `bar` should be called.
  int n;
  /// @brief A boolean flag that controls whose turn it is to run.
  /// `true` indicates it's `foo`'s turn, `false` indicates it's `bar`'s turn.
  bool isFooTime;
  /// @brief The mutex used to protect the `isFooTime` flag and the condition variable.
  mutex isFooTimeMtx;
  /// @brief The condition variable used to block and unblock threads based on whose turn it is.
  condition_variable isFooTimeCV;

 public:
  /// @brief Constructs a new FooBar object.
  /// @param n The number of alternating `foo` and `bar` calls.
  FooBar(int n) {
    this->n = n;
    this->isFooTime = true;
  }

  /// @brief Executes the `foo` part of the sequence.
  ///
  /// This method waits until it is its turn (`isFooTime` is true),
  /// executes its action, then signals to `bar` that its turn has ended.
  /// @param printFoo A callable object to be executed when it's `foo`'s turn.
  void foo(function<void()> printFoo) {
    for (int i = 0; i < this->n; i++) {
      unique_lock<mutex> lock(this->isFooTimeMtx);
      this->isFooTimeCV.wait(lock, [this]() { return this->isFooTime; });

      printFoo();

      this->isFooTime = false;
      this->isFooTimeCV.notify_one();
    }
  }

  /// @brief Executes the `bar` part of the sequence.
  ///
  /// This method waits until it is its turn (`isFooTime` is false),
  /// executes its action, then signals to `foo` that its turn has ended.
  /// @param printBar A callable object to be executed when it's `bar`'s turn.
  void bar(function<void()> printBar) {
    for (int i = 0; i < this->n; i++) {
      unique_lock<mutex> lock(this->isFooTimeMtx);
      this->isFooTimeCV.wait(lock, [this]() { return !this->isFooTime; });

      printBar();

      this->isFooTime = true;
      this->isFooTimeCV.notify_one();
    }
  }
};