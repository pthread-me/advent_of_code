def max_jolt1(l: list[str]):

    pos, left = max(enumerate(l[:-2]), key=lambda x: x[1]) 
    right = max(l[pos+1:])
    
    print(left+right)
    return int(left+right)


def max_jolt2(l: list[str]):
    res: list[str] = []
    prev = 0
    for i in range(-11, 1):
        mi, mv = prev,l[prev]
        for j in range(prev, len(l)+i):
            if mv<l[j]:
                mv = l[j]
                mi = j

        res += mv
        prev = mi+1
    
    return int("".join(res))


    
if __name__ == "__main__":
    file = open("inputs/2025/03/input.txt", "r")
#    file = open("inputs/2025/03/sample.txt", "r")
  
    res: int = 0
    for line in file:
        res += max_jolt2(list(line.strip()))

    print(res)
