"""
Aledutron
SPPU 2019 TE AI Lab
SPPU Computer Engineering Third Year (TE) Artificial Intelligence (AI) Lab Assignments (2019 Pattern)
Youtube AI Lab Playlist Link: https://www.youtube.com/playlist?list=PLlShVH4JA0ot3KGVHgl8FVTl8-JNCrPP5

Problem Statement:
Group-B/Q4A.py
Implement a solution for a Constraint Satisfaction Problem using Branch and Bound and Backtracking for n-queens problem.

Explaination Video Link: https://www.youtube.com/watch?v=1j9vvQWVblc&list=PLlShVH4JA0ot3KGVHgl8FVTl8-JNCrPP5&index=3&pp=iAQB
"""

N = int(input())

queen = "Q"
empty = "-"

# N = 4

# [
# [0,0,0,0],
# [0,0,0,0],
# [0,0,0,0],
# [0,0,0,0]
# ]

b = [[empty] * N for i in range(N)]


# for j in range(N):
# 	temp = []
# 	for i in range(N):
# 		temp.append(0)
# 	b.append(temp)

# print(b)

def isSafe(i, j):
    for p in range(N):
        if b[i][p] == queen or b[p][j] == queen:
            return False

    for n in range(N):
        for m in range(N):
            if i+j == n+m or i-j == n-m:
                if b[n][m] == queen:
                    return False

    return True


def nqueen(noq):
    if noq == 0:
        return True

    for i in range(N):
        for j in range(N):
            if b[i][j] != queen and isSafe(i, j):
                b[i][j] = queen
                if nqueen(noq-1) == True:
                    return True
                b[i][j] = empty

    return False


def printBoard(b):
    for i in b:
        for j in i:
            print(j, end=" ")
        print()


if nqueen(N):
    printBoard(b)
else:
    print("Can't Place")
