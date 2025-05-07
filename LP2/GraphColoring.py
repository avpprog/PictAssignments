"""
Aledutron
SPPU 2019 TE AI Lab
SPPU Computer Engineering Third Year (TE) Artificial Intelligence (AI) Lab Assignments (2019 Pattern)
Youtube AI Lab Playlist Link: https://www.youtube.com/playlist?list=PLlShVH4JA0ot3KGVHgl8FVTl8-JNCrPP5

Problem Statement:
Group-B/Q4B.py
Implement a solution for a Constraint Satisfaction Problem using Branch and Bound and Backtracking for a graph coloring problem.

Explaination Video Link: https://www.youtube.com/watch?v=N1qfrKSbS1Q&list=PLlShVH4JA0ot3KGVHgl8FVTl8-JNCrPP5&index=4&pp=iAQB
"""

m = int(input("Enter Number of Max Colors: "))

g = {}

n = int(input("Enter number of Edges: "))

for i in range(n):
    a, b = map(int, input().split())
    if g.get(a) == None:
        g[a] = []
    g[a].append(b)
    if g.get(b) == None:
        g[b] = []
    g[b].append(a)

print(g)

"""
3
6
0 1
0 2
0 3
1 2
2 3
3 4
"""

posCol = ["red", "orange", "violet", "indigo", "blue", "yellow", "green"]


def canColour(g, n, col, colList):
    for child in g[n]:
        if colList[child] == posCol[col]:
            return False

    return True


def graphColouring(g, m, v, n, colList):
    if n == v:
        return True

    for col in range(m):
        if canColour(g, n, col, colList):
            colList[n] = posCol[col]
            if graphColouring(g, m, v, n+1, colList) == True:
                return True
            colList[n] = -1


colList = {}

for i in g.keys():
    colList[i] = -1

if graphColouring(g, m, len(g.keys()), 0, colList):
    print(colList)
else:
    print(f"Can't colour using m = {m} colors")
