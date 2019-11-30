import longest_path
from collections import defaultdict


def read_graph(filename):
    graph = defaultdict(list)
    with open(filename) as f:
        vert_count = int(f.readline())
        edge_count = int(f.readline())
        for _ in range(edge_count):
            start, end = map(int, f.readline().split())
            graph[start].append(end)
            graph[end]
    return graph



def test_longest_path():
    graph = read_graph('graph_example')
    path = longest_path.longest_path(graph)
    print(path)


if __name__ == '__main__':
    test_longest_path()

    