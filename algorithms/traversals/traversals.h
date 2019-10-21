#include <iostream>
#include <queue>


template <class T>
struct Node {
  T key;
  Node* parent;
  Node* first_child;
  Node* next_sibling;

  Node(T key): key(key), parent(NULL), first_child(NULL), next_sibling(NULL) {}
};

template <class T>
void node_process(Node<T>* node) {
  std::cout << node->key << "; ";
}

// preorder
template <class T>
void preorder_recursive_traversal(Node<T>* root) {
  if (root == NULL) {
    return;
  }
  node_process(root);
  Node<T>* node = root->first_child;
  while (node != NULL) {
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
void recursive_BFS(Node<T>* root, std::queue<Node<T>*>* queue=nullptr) {
  if (!queue) {
    queue = new std::queue<Node<T>*>();
    queue->push(root);
  }
  std::queue<Node<T>*> next_level;
  while (!queue->empty()) {
    Node<T>* curr = queue->front();
    queue->pop();
    while (curr) {
      node_process(curr);
      next_level.push(curr->first_child);
      curr = curr->next_sibling;
    }
  }
  if (!next_level.empty())
    recursive_BFS(root, &next_level);
}

template <class T>
void iterative_BFS(Node<T>* root) {
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
