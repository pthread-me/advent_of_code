
def invalid(nums: str)->bool:
    n:int = len(nums)//2
    if nums[:n] == nums[n:]:
        return True
    return False

def invalid2(num: str)-> bool:
    dic: dict[str, int] = {}
    for i in range(1, len(num)):
        for j in range(0, i):
            if num[j:i] == num[i:i+(i-j)]:
                if num[j:i] in dic:
                    dic[num[j:i]] +=1
                else:
                    dic[num[j:i]] = 2
    
    repeat: list[str] = [k for k in dic if dic[k]>=2]
#    print(dic)

    return any(k for k in repeat if k*dic[k] == num)

if __name__ == "__main__":
    file = open("inputs/2025/02/input.txt", "r")
 #   file = open("inputs/2025/02/sample.txt", "r")
    line: list[str] = []
    line = file.readline().split(",")
    res: int = 0
   
    for p in line:
        [l,r] = p.split("-")
        for i in range(int(l),int(r)+1):
            if invalid2(str(i)):
                res += i
#                print(i)
    
    print(res)
