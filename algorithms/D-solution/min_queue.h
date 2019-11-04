#include <stack>
#include <limits>


template <class T>
class MinQueue {
 public:
  MinQueue(T max): input_min_(max) {}
  MinQueue(): input_min_(std::numeric_limits<T>::max()) {}
  void push(T val);
  T pop();
  bool empty() const;
  size_t size() const;
  T min() const;


 private:
  std::stack<T> input_, output_, output_stack_;
  T input_min_;
};

template <class T>
void MinQueue<T>::push(T val) {
  input_.push(val);
  input_min_ = std::min(input_min_, val);
}

template <class T>
T MinQueue<T>::pop() {
  if (empty()) {
    throw std::runtime_error("pop() from empty minQueue");
  }
  if (output_.empty()) {
    input_min_= std::numeric_limits<T>::max();
    while (!input_.empty()) {
      output_.push(input_.top());
      if (output_stack_.empty() || output_stack_.top() >= input_.top()) {
        output_stack_.push(input_.top());
      }
      input_.pop();
    }
  }
  const T& temp = output_.top();
  output_.pop();
  if (temp == output_stack_.top()) {
    output_stack_.pop();
  }
  return temp;
}

template <class T>
bool MinQueue<T>::empty() const {
  return input_.empty() && output_.empty();
}

template <class T>
size_t MinQueue<T>::size() const {
  return input_.size() + output_.size();
}

template <class T>
T MinQueue<T>::min() const {
  return output_stack_.empty() ? input_min_ :
         input_min_ ? output_stack_.top() : std::min(output_stack_.top(), input_min_);
}