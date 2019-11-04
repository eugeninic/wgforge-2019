#include <stack>


template <typename T>
class Queue {
 private:
  std::stack<T> input_;
  std::stack<T> output_;
  
 public:
  void push(T val);
  T pop();
  bool empty() const;
  size_t size() const;
};


template <typename T>
T Queue<T>::pop() {
  if (empty()) {
    throw std::runtime_error("pop() from empty queue");
  }
  if (output_.empty()) {
    while (!input_.empty()) {
      output_.push(input_.top());
      input_.pop();
    }
  }
  T temp = output_.top();
  output_.pop();
  return temp;
}

template <typename T>
void Queue<T>::push(T val) {
  input_.push(val);
}

template <typename T>
bool Queue<T>::empty() const {
  return input_.empty() && output_.empty();
}

template <typename T>
size_t Queue<T>::size() const {
  return input_.size() + output_.size();
}