#include <stack>
#include <limits>


template <class T>
class MinQueue {
 public:
  MinQueue(): min_(std::numeric_limits<T>::max()) {}
  void push(T val);
  T pop();

  bool empty() const {
    return input_.empty() && output_.empty();
  }

  size_t size() const {
    return input_.size() + output_.size();
  }

  const T& min() const {
    if (!min_ && min_stack_.empty()) {
      throw std::runtime_error("min() from empty minQeueu");
    }
    return min_stack_.empty()? min_ :
             min_? min_stack_.top() : std::min(min_stack_.top(), min_);
  }

 private:
  std::stack<T> input_, output_, min_stack_;
  T min_;
};

template <class T>
void MinQueue<T>::push(T val) {
  input_.push(val);
  min_ = std::min(min_, val);
}

template <class T>
T MinQueue<T>::pop() {
  if (empty()) {
    throw std::runtime_error("pop() from empty minQueue");
  }
  if (output_.empty()) {
    min_= std::numeric_limits<T>::max();
    while (!input_.empty()) {
      output_.push(input_.top());
      if (min_stack_.empty() || min_stack_.top() >= input_.top()) {
        min_stack_.push(input_.top());
      }
      input_.pop();
    }
  }
  const T& temp = output_.top();
  output_.pop();
  if (temp == min_stack_.top()) {
    min_stack_.pop();
  }
  return temp;
}