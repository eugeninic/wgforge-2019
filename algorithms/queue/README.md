# Задание

Написать алгоритм реализации очереди с использованием двух стеков.

## Очередь на двух стеках

Один из вариантов реализации очереди - реализация очереди на двух стеках.

Пусть у нас есть два стека, назовём их `input` стек и `output` стек. 

* `input` стек используется для `push` операций. 
* `output` стек используется для `pop` операций.


Алгоритм можно описать следующим образом:

* Если необходимо добавить элемент в очередь, то делается `push` операция в `input` стек.

* Если необходимо удалить элемент из очереди, то:
  1. если `output` стек не пуст, то из него просто удаляется элемент
  2. если же он пуст, то все элементы из `input` стека переносятся в `output` стек (причём все элементы `input` стека в `output` стеке оказываются в обратном порядке, что и необходимо при удалении)

#### Сложность

Сложность: амортизированная `O(1)`.

Можно доказать, если для каждой операции `push` вместо 1 операции считать 3 (`push`, перемещении из `input` в `output`, `pop`). Тогда сложность `pop` можно считать равной 0 (почитали в `push`). 

Таким образом сложность для каждой операции равна `O(1)`.

#### Замечания

К плюсам данной очереди можно отнести то, что её несложно модифицировать для получения максимума (минимума) за `O(1)`.
   
К минусам, что в случае пустого `output` стека операция `pop` будет выполнятся за `O(n)` (есть [реализация очереди](https://neerc.ifmo.ru/wiki/index.php?title=%D0%9F%D0%B5%D1%80%D1%81%D0%B8%D1%81%D1%82%D0%B5%D0%BD%D1%82%D0%BD%D0%B0%D1%8F_%D0%BE%D1%87%D0%B5%D1%80%D0%B5%D0%B4%D1%8C#.D0.A0.D0.B5.D0.B0.D0.BB.D0.B8.D0.B7.D0.B0.D1.86.D0.B8.D1.8F_.D0.BE.D1.87.D0.B5.D1.80.D0.B5.D0.B4.D0.B8_.D0.BD.D0.B0_.D1.88.D0.B5.D1.81.D1.82.D0.B8_.D1.81.D1.82.D0.B5.D0.BA.D0.B0.D1.85) на стеках, у которой все операции выполняются за чистые `O(1)`)

#### [Реализация](queue.cpp)

```cpp
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
```


## Очереди на двух стеках с поиском минимума или максимума за _O(1)_

В очереди на двух стеках можно реализовать операции поиска максимума и минимума за `O(1)`.

Для этого необходимо добавить дополнительное поле, которое будет хранить максимальное (минимальное) значение во входном стеке, а также ещё один стек (можно не добавлять, а хранить всё в выходном стеке: текущий элемент и максимум (минимум) на данный момент), который будет хранить текущий максимум (минимум) в выходном стеке.

Тогда, зная максимум (минимум) во входном и выходном стеках, находим максимум (минимум) между ними за `O(1)`, однако в худшем случае потребуется в два раза больше памяти (если элементы буду добавляться в порядке возрастания (убывания) для поиска максимума (минимума)).

#### [Реализация](max_queue.h)

```cpp
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
```