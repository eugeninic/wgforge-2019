#include <stack>


template <class T>
class Queue {
 public:
  void push(const T& val);
  const T& pop();
  bool empty() const;
  size_t size() const;

 private:
  std::stack<T> input_, output_;
};


template <class T>
const T& Queue<T>::pop() {
  if (empty()) {
    throw std::runtime_error("pop() from empty queue");
  }
  if (output_.empty()) {
    while (!input_.empty()) {
      output_.push(input_.top());
      input_.pop();
    }
  }
  const T& temp = output_.top();
  output_.pop();
  return temp;
}

template <class T>
void Queue<T>::push(const T& val) {
  input_.push(val);
}

template <class T>
bool Queue<T>::empty() const {
  return input_.empty() && output_.empty();
}

template <class T>
size_t Queue<T>::size() const {
  return input_.size() + output_.size();
}