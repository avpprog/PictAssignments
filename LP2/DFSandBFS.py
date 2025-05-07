"""
Aledutron
SPPU 2019 TE AI Lab
SPPU Computer Engineering Third Year (TE) Artificial Intelligence (AI) Lab Assignments (2019 Pattern)
Youtube AI Lab Playlist Link: https://www.youtube.com/playlist?list=PLlShVH4JA0ot3KGVHgl8FVTl8-JNCrPP5

Problem Statement:
Group-A/Q1.py
Implement depth first search algorithm and Breadth First Search algorithm, Use an undirected graph and develop a recursive algorithm for searching all the vertices of a graph or tree data structure.

Explaination Video Link: https://www.youtube.com/watch?v=Esh4Qf_t9Bw&list=PLlShVH4JA0ot3KGVHgl8FVTl8-JNCrPP5&index=1&pp=iAQB
"""

g = {
    0: [1, 2],
    1: [0, 3, 4],
    2: [3, 0],
    3: [2, 1, 4],
    4: [3, 1]
}


def dfs(g, s):
    vis[s] = 1
    print(s)
    for c in g[s]:
        if not vis[c]:
            dfs(g, c)

# vis = [0] * 5

# dfs(g,0)


def bfs(g, s):
    q = [s]
    vis = [s]
    while q:
        cur = q.pop(0)
        print(cur)
        for c in g[cur]:
            if c not in vis:
                q.append(c)
                vis.append(c)


bfs(g, 0)
