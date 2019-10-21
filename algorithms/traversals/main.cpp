#include "traversals.h"

int main() {
  Node<int> A(1), B(2), C(3), D(4), E(5), F(6), G(7), H(8);
  A.first_child = &B;
  B.next_sibling = &C;
  C.next_sibling = &D;
  B.parent = &A;
  C.parent = &A;
  D.parent = &A;
  C.first_child = &E;
  E.next_sibling = &F;
  F.parent = &C;
  E.parent = &C;
  D.first_child = &G;
  G.parent = &D;
  G.first_child = &H;
  H.parent = &G;

  preorder_recursive_traversal(&A);
  std::cout << std::endl;
  preorder_iterative_traversal(&A);
  std::cout << std::endl << std::endl;
  postorder_recursive_traversal(&A);
  std::cout << std::endl;
  postorder_iterative_traversal(&A);

  std::cout << std::endl << std::endl;
  iterative_BFS(&A);
  std::cout << std::endl;
  recursive_BFS(&A);
  std::cout << std::endl;
}