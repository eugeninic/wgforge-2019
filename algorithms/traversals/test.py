from node import Node
from traversals import (postorder_recursive_traversal, postorder_iterative_traversal, 
           preorder_iterative_traversal, preorder_recursive_traversal, iterative_bfs)

A = Node('A')
B = Node('B')
C = Node('C')
D = Node('D')
E = Node('E')
F = Node('F')
G = Node('G')

k1 = Node("K1")
k2 = Node("K2")

root = B
B.left_child = A
A.parent = B
A.right_sibling = C
C.parent = B
C.left_child = D
C.right_sibling = F
F.parent = B
F.left_child = G
G.parent = F
D.parent = C
D.right_sibling = E
E.parent = C

E.left_child = k1
k1.parent = E
k2.parent = E
k1.right_sibling = k2


iterative_bfs(root)
print()
preorder_recursive_traversal(root)
print()
preorder_iterative_traversal(root)
print()
postorder_recursive_traversal(root)
print()
postorder_iterative_traversal(root)
print()