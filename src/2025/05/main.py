#!/usr/bin/python3


def in_range(i: int, ranges: list[list[int]])->bool:
    for r in ranges:
        if r[0]<=i<=r[1]:
            return True

    return False

def part2(ranges: list[list[int]]) -> int:
    disjoint: list[list[int]] = [ranges[0]]
    res: int = 0

    for r in ranges[1:]:
        if r[0] <= disjoint[-1][1]:
            disjoint[-1][1] = r[1]
        else:
            disjoint.append(r)
    
    for r in disjoint:
        res += (r[1]-r[0]+1)
    
    return res 
if __name__ == "__main__":
    input = open("inputs/2025/05/input.txt")
#    sample = open("inputs/2025/05/sample.txt")


    file = input
    
    ranges: list[list[int]] = []
    
    for line in file:
        if "-" in line:
            r = line.strip().split("-")
            ranges.append(sorted([int(r[0]), int(r[1])]))

    ranges.sort()
    print(part2(ranges))
    
  
