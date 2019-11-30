import prim
from collections import defaultdict


#TODO  save in hashtable
def read_graph(filename):
    graph = defaultdict(list)
    with open(filename) as f:
        vert_count = int(f.readline())
        edge_count = int(f.readline())
        for _ in range(edge_count):
            start, end, weight = map(int, f.readline().split())
            graph[start].append((end, weight))
            graph[end].append((start, weight))
    return graph



def test_prim_algorithm():
    graph = read_graph('graph_example')
    edges, mst_weight = prim.fibonacci_heap_mst(graph)
    print("Fibonacci heap MST edges:", edges)
    print("Fibonacci heap MST weigth", mst_weight)
    edges, mst_weight = prim.binary_heap_mst(graph)
    print("Binary head MST edges:", edges)
    print("Binary MST weigth", mst_weight)


if __name__ == '__main__':
    test_prim_algorithm()
