#include "traversals.h"

int main() {
  Node<int> A(1), B(2), C(3), D(4), E(5), F(6), G(7), H(8), k1(9), k2(10), k3(11);
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

  std::cout << "Preorder traversals: " << std::endl;
  preorder_recursive_traversal(&A);
  std::cout << std::endl;
  preorder_iterative_traversal(&A);

  std::cout << std::endl << std::endl;
  std::cout << "Inorder traversals: " << std::endl;
  postorder_recursive_traversal(&A);
  std::cout << std::endl;
  postorder_iterative_traversal(&A);

  std::cout << std::endl << std::endl;
  std::cout << "BFS traversals: " << std::endl;
  iterative_bfs(&A);
  std::cout << std::endl;
  recursive_bfs(&A);
  std::cout << std::endl;
  recursive_bfs_for_every_element(&A);
}