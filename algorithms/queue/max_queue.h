#include <stack>


template <typename T>
class MaxQueue {
 private:
  std::stack<T> input_;
  std::stack<T> output_;
  std::stack<T> output_max_;
  T input_max_;

 public:
  void push(T val);
  T pop();
  T max() const;
  bool empty() const;
  size_t size() const;
};

template <typename T>
void MaxQueue<T>::push(T val) {
  if (input_.empty()) {
    input_max_ = val;
  } else {
    input_max_ = std::max(input_max_, val);
  }
  input_.push(val);
}

template <typename T>
T MaxQueue<T>::pop() {
  if (output_.empty() && input_.empty()) {
    throw std::runtime_error("pop() from empty MaxQueue");
  }
  if (output_.empty()) {
    while (!input_.empty()) {
      output_.push(input_.top());
      if (output_max_.empty() || output_max_.top() <= input_.top()) {
        output_max_.push(input_.top());
      }
      input_.pop();
    }
  }
  if (output_.top() == output_max_.top()) {
    output_max_.pop();
  }
  T temp = output_.top();
  output_.pop();
  return temp;
}

template <typename T>
T MaxQueue<T>::max() const {
  if (input_.empty() && output_.empty()) {
    throw std::runtime_error("max() from empty MaxQueue");
  }
  if (input_.empty()) {
    return output_max_.top();
  }
  if (output_max_.empty()) {
    return input_max_;
  }
  return std::max(output_max_.top(), input_max_);
}

template <typename T>
bool MaxQueue<T>::empty() const {
  return input_.empty() && output_.empty();
}

template <typename T>
size_t MaxQueue<T>::size() const {
  return input_.size() + output_.size();
}