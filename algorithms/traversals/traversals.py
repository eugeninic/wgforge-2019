from node import Node
from collections import deque


def node_process(node: Node):
    """fuction for process node"""
    print(node, end='; ')


def preorder_recursive_traversal(root: Node):
    if not root:
        return
    node_process(root)
    node = root.left_child
    while node:
        preorder_recursive_traversal(node)
        node = node.right_sibling


def preorder_iterative_traversal(root: Node):
    while root:
        node_process(root)
        if root.left_child:
            root = root.left_child
        else:
            while root and not root.right_sibling:
                root = root.parent
            if root:
                root = root.right_sibling


def postorder_recursive_traversal(root: Node):
    if not root:
        return
    node = root.left_child
    while node:
        postorder_recursive_traversal(node)
        node = node.right_sibling
    node_process(root)


def postorder_iterative_traversal(root: Node):
    while root:
        if root.left_child:
            root = root.left_child
        else:
            while root and not root.right_sibling:
                node_process(root)
                root = root.parent
            if root:
                node_process(root)
                root = root.right_sibling


def recursive_bfs(root: Node):
    pass


def iterative_bfs(root: Node):
    deq = deque()
    deq.append(root)
    while deq:
        curr_level = []
        while deq:
            node = deq.popleft()
            while node:
                if node.left_child:
                    curr_level.append(node.left_child)
                node_process(node)
                node = node.right_sibling
        deq.extend(curr_level)
        print()  # for print blank line between different levels
