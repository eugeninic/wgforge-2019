import heapq
from collections import deque
from fibonacci_heap import FibonacciHeap

# lazy algorithm Prima O(E * log(V))
def binary_heap_mst(graph):
    heap = []
    mst = set()
    edges = []
    tree_weight = 0
    next_vert = next(iter(graph.keys()))
    mst.add(next_vert)
    while len(mst) < len(graph):
        v = next_vert
        for vert, weight in graph[v]:
            heapq.heappush(heap, (weight, v, vert))

        while heap[0][2] in mst:
            heapq.heappop(heap)

        weight, v1, v2 = heap[0]
        heapq.heappop(heap)
        next_vert = v2
        mst.add(v2)
        edges.append((v1, v2))
        tree_weight += weight
 
    return edges, tree_weight


def fibonacci_heap_mst(graph):
    fheap = FibonacciHeap()
    nodes = {}
    mst_weight = 0
    edges = []
    mst = set()
    for v in graph:
        nodes[v] = fheap.insert((float('inf'), -1, -1))

    next_vert = next(iter(graph.keys()))
    mst.add(next_vert)
    while len(mst) < len(graph):
        v = next_vert
        for vert, weight in graph[v]:
            if vert not in mst:
                fheap.decrease_key(nodes[vert], (weight, v, vert))

        weight, v1, v2 = fheap.extract_min().key
        next_vert = v2
        mst.add(v2)
        edges.append((v1, v2))
        mst_weight += weight

    return edges, mst_weight
    
