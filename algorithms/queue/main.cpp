#include <iostream>
#include "queue.h"


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
        std::cout << "Poped element: " << q.pop() << std::endl;
        break;

    }
    std::cout << "Empty: " << q.empty() << ", size: " << q.size() << std::endl;
  }
  return 0;
}