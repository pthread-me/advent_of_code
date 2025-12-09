

def part1(grid: list[list[str]], pos: tuple[int, int])->int:

    i,j = pos
    seen = {}

    def rec(i:int,j:int)->int:

        while i+1<len(grid) and grid[i+1][j] != "^":
            i+=1

        if i == len(grid)-1:
            return 0
        else:
            if (i,j) in seen:
                return 0
            seen[(i,j)] = 0
            print("seen")
            print(seen)
            left: int = part1(grid, (i,j-1)) if j-1>-1 else 0
            right: int = part1(grid, (i,j+1)) if j+1<len(grid[0]) else 0
            return 1+left+right
        
    return rec(i,j)
    



if __name__ == "__main__":
    input = open("inputs/2025/07/input.txt", "r")
    sample = open("inputs/2025/07/sample.txt", "r")
    
    grid: list[list[str]] =[]
    file = sample

    for line in file:
        grid.append(list(line.strip()))
    
    j=0
    while j<len(grid[0]):
        if grid[0][j] == "S":
            break
        else:
            j+=1
    
    print(part1(grid, (0,j)))

