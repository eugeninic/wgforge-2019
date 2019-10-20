#include <iostream>
#include "queue.h"

// TODO : references in c++

int main() {
  Queue<int> q;
  while (true) {
    int code, b;
    std::cin >> code >> b;
    switch (code) {
      case -1:
        return 0;
      case 1:
        q.push(b);
        break;
      case 2:
        std::cout << q.pop() << std::endl;
        break;

    }
    std::cout  << q.empty() << "; " << q.size() << std::endl;
  }
  return 0;
}