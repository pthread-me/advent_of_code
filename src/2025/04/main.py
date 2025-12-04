dir: list[list[int]] = [[-1,-1], [-1,0], [-1,1],[0,-1],[0,1],[1,-1], [1,0], [1,1]]

def part1(grid: list[list[str]])->int:
    res: int = 0
    
    def check(i:int, j:int):
        count: int = 0
        for d in dir:
            if -1<i+d[0]<len(grid) and -1< j+d[1]<len(grid[0]):
                if grid[i+d[0]][j+d[1]] == "@":
                    count += 1
        return count


    for i in range(0, len(grid)):
        for j in range(0, len(grid[0])):
            if grid[i][j] == "@" and check(i,j) <4:
                grid[i][j] = "."
                res +=1

    return res


if __name__ == "__main__":
    file = open("inputs/2025/04/input.txt", "r")
#    file = open("inputs/2025/04/sample.txt", "r")

    res: int = 0
    grid: list[list[str]] = []
    for line in file:
        grid.append([e for e in line.strip()])
    
    while True:
        cur = part1(grid)
        if cur == 0: break
        res += cur

    print(res)
