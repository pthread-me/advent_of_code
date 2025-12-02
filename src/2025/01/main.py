



if __name__ == "__main__":
    file = open("inputs/2025/01/input.txt", "r")
    zeros: list[int] = [0]
    cur: int = 50
    
    def rotate(dir:str, val: int) -> int:
        if val >= 100:
            zeros[0] += val//100 
        val = val%100

        if dir == "L":
            if cur != 0 and cur - val <= 0:
                zeros[0] +=1
            return (cur - val)%100 
        else:
            if cur + val >99:
                zeros[0] +=1
            return (cur + val)%100 
        

    for l in file:
        dir: str = l[0]
        num: int = int(l[1:])
        cur = rotate(dir, num)
        print(cur, zeros)
    print(zeros)
