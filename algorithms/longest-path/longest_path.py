from collections import defaultdict


def dfs(curr, G, visited, dp):
    if visited[curr]:
        return dp[curr]
    visited[curr] = True
    max_length = 0
    for vert in G[curr]:
        max_length = max(max_length, dfs(vert, G, visited, dp))
    dp[curr] = max_length + 1
    return dp[curr]


def restore_path(G, dp):
    idx = max_length = -1
    for i, length in dp.items():
        if length > max_length:
            max_length = length
            idx = i

    path = []
    
    while max_length > 0:
        path.append(idx)
        max_length -= 1
        for vert in G[idx]:
            if dp[vert] == max_length:
                idx = vert
                break

    return path        


def longest_path(G):
    visited = {vert: False for vert in G}
    dp = defaultdict(int)
    for vert in G:
        if not visited[vert]:
            dfs(vert, G, visited, dp)

    return restore_path(G, dp)