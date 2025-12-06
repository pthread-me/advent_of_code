#!/usr/bin/python3


def part1(col:list[int], op: str) -> int:
    print(col, op)
    if op == "+":
        return sum(col)
    else:
        res = col[0]
        for e in col[1:]:
            res *= e
        return res


def part2(col: list[str], op: str, n:int):
    c: list[str] = ["" for _ in range(n)]
    for i in range(n):
        for j in range(len(col)):
            c[i] += col[j][i] if col[j][i] != "_" else "" 
        if c[i] == "":
            c[i] = "0"
    print(c)
    nums = [int(e) for e in c]
    if op=="+":
        res = sum(nums)
    else:
        res = nums[0]
        for e in nums[1:]:
            res *= e
    
    print(nums, res)
    return res

if __name__ == "__main__":
    input = open("inputs/2025/06/input.txt", "r")
    sample = open("inputs/2025/06/sample.txt", "r")


    file = input
    mat: list[list[str]] = []
    raw: list[str] = []
    res = 0

    for line in file:
        l = line.strip("\n")
        raw.append(l)
        mat += [l.split()]
    
    
    col: list[list[str]] = [["" for _ in range(len(mat)-1)] for _ in range(len(mat[0]))]
    for i in range(0, len(mat)-1):
        for j in range(0, len(mat[0])):
            col[j][i] = mat[i][j]
    
    
    justify_dis: list[int] = []
    for i in range(0, len(col)):
        justify_dis.append( len(str(max([int(e) for e in col[i]]))))
    
    
    just_col: list[list[str]] = [["" for _ in range(len(justify_dis))] for _ in range(len(mat)-1)]
    for i in range(0, len(just_col)):
        j = 0
        pos = 0
        while j<len(justify_dis):
            for k in range(0,justify_dis[j]):
                just_col[i][j] += raw[i][pos] if raw[i][pos] != " " else "_"
                pos += 1
            pos +=1
            j+=1
    
    grid: list[list[str]] = [["" for _ in range(len(just_col))] for _ in range(len(just_col[0]))]
    for i in range(len(just_col)):
        for j in range(len(just_col[0])):
            grid[j][i] = just_col[i][j]

    res = 0
    for i in range(len(grid)):
#        print(grid[i], mat[-1][i])
        res += part2(grid[i], mat[-1][i], justify_dis[i])
    print(res)
