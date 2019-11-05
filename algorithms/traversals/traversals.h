#include <iostream>
#include <queue>


template <class T>
struct Node {
  T key;
  Node* parent;
  Node* first_child;
  Node* next_sibling;

  Node(T key): key(key), parent(nullptr), first_child(nullptr), next_sibling(nullptr) {}
};

template <class T>
void node_process(Node<T>* node) {
  std::cout << node->key << "; ";
}

// preorder
template <class T>
void preorder_recursive_traversal(Node<T>* root) {
  if (!root) {
    return;
  }
  node_process(root);
  Node<T>* node = root->first_child;
  while (node) {
    preorder_recursive_traversal(node);
    node = node->next_sibling;
  }
}

template <class T>
void preorder_iterative_traversal(Node<T>* root) {
  while (root) {
    node_process(root);
    if (root->first_child) {
      root = root->first_child;
    } else {
      while (root && !root->next_sibling) {
        root = root->parent;
      }
      if (root) {
        root = root->next_sibling;
      }
    }
  }
}


// postorder
template <class T>
void postorder_recursive_traversal(Node<T>* root) {
  if (!root) {
    return;
  }
  Node<T>* node = root->first_child;
  while (node) {
    postorder_recursive_traversal(node);
    node = node->next_sibling;
  }
  node_process(root);
}

template <class T>
void postorder_iterative_traversal(Node<T>* root) {
  while (root) {
    if (root->first_child) {
      root = root->first_child;
    } else {
      while (root && !root->next_sibling) {
        node_process(root);
        root = root->parent;
      }
      if (root) {
        node_process(root);
        root = root->next_sibling;
      }
    }
  }
}


// breadth first search
template <class T>
void recursive_bfs(Node<T>* root, std::queue<Node<T>*>* queue= nullptr) {
  if (!queue) {
    queue = new std::queue<Node<T>*>();
    queue->push(root);
  }
  std::queue<Node<T>*>* next_level = new std::queue<Node<T>*>();
  while (!queue->empty()) {
    Node<T>* curr = queue->front();
    queue->pop();
    while (curr) {
      node_process(curr);
      next_level->push(curr->first_child);
      curr = curr->next_sibling;
    }
  }
  delete queue;
  if (!next_level->empty())
    recursive_bfs(root, next_level);
  else
    delete next_level;
}

template <class T>
void recursive_bfs_for_every_element(Node<T>* node) {
  if (!node) {
    return;
  }
  node_process(node);
  // глубина, на которую необходимо спуститься,
  // чтобы оказаться на текущем уровне
  int deepness = 0;
  // проверяем, что текущий уровень ещё не закончился
  while (n3ode->parent && !node->next_sibling) {
    node = node->parent;
    ++deepness;
  }
  // если текущий уровень закончился, то увеливаем глубину (номер уровня),
  // на которую затем необходимо спуститься
  if (!node->parent) {
    ++deepness;
  } else { // если не закончился, то переходим на следующий элемент или выходим из рекурсии, так как этот элемент последний
    node = node->next_sibling;
  }
  // находим следующий элемент на данном уровне
  // или не находим, так как он последний, и выходим из рекурсии
  while (node && deepness != 0) {
    if (node->first_child) {
      node = node->first_child;
      --deepness;
    } else {
      while (node && !node->next_sibling) {
        node = node->parent;
        ++deepness;
      }
      if (node) {
        node = node->next_sibling;
      }
    }
  }
  recursive_bfs_for_every_element(node);
}

template <class T>
void iterative_bfs(Node<T>* root) {
  std::queue<Node<T>*> queue;
  queue.push(root);
  while (!queue.empty()) {
    Node<T>* curr = queue.front();
    queue.pop();
    while (curr) {
      node_process(curr);
      queue.push(curr->first_child);
      curr = curr->next_sibling;
    }
  }
}