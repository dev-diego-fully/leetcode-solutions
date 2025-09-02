/// @brief Defines the Foo class for sequential method execution.

#include <condition_variable>
#include <functional>
#include <mutex>

using std::condition_variable;
using std::function;
using std::mutex;
using std::unique_lock;

/// @class Foo
/// @brief A class that ensures three methods are executed in a specific order: first(), then second(), then third().
///
/// This class uses `std::condition_variable` and `std::mutex` to synchronize
/// the execution of its public methods, guaranteeing that the sequence `first` -> `second` -> `third`
/// is strictly followed, even if the methods are called from different threads.
class Foo {
 public:
  /// @brief Constructs a new Foo object.
  Foo() {}

  /// @brief Executes the first step of the sequence.
  ///
  /// This method performs its action and then signals to unblock the thread waiting on `second()`.
  /// @param printFirst A callable object that performs the action for the first step.
  void first(function<void()> printFirst) {
    printFirst();
    this->hasFirstEnded.notify_one();
  }

  /// @brief Executes the second step of the sequence.
  ///
  /// This method waits for the `first()` method to finish before executing its action.
  /// After its action is complete, it signals to unblock the thread waiting on `third()`.
  /// @param printSecond A callable object that performs the action for the second step.
  void second(function<void()> printSecond) {
    unique_lock<mutex> lock(this->mtxHasFirstEnded);
    this->hasFirstEnded.wait(lock);

    printSecond();

    this->hasSecondedEnded.notify_one();
  }

  /// @brief Executes the third and final step of the sequence.
  ///
  /// This method waits for the `second()` method to finish before executing its action.
  /// @param printThird A callable object that performs the action for the third step.
  void third(function<void()> printThird) {
    unique_lock<mutex> lock(this->mtxHasSecondedEnded);
    this->hasSecondedEnded.wait(lock);

    printThird();
  }

 private:
  /// @brief Condition variable that signals the completion of the first step.
  condition_variable hasFirstEnded;
  /// @brief Condition variable that signals the completion of the second step.
  condition_variable hasSecondedEnded;
  /// @brief Mutex used to protect the `hasFirstEnded` condition variable.
  mutex mtxHasFirstEnded;
  /// @brief Mutex used to protect the `hasSecondedEnded` condition variable.
  mutex mtxHasSecondedEnded;
};