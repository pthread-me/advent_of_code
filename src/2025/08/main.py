from math import sqrt
Point = tuple[int,int,int]

class DisjointSet:
    def __init__(self, p: list[Point]):
        self.parents: dict[Point, Point] = {}
        self.size: dict[Point, int] = {}
        for e in p:
            self.make_set(e)

    def make_set(self, p: Point):
        self.parents[p] = p
        self.size[p] = 1
    

    def find_set(self, p: Point)->Point:
        if p == self.parents[p]:
            return p

        self.parents[p] = self.find_set(self.parents[p])
        return self.parents[p]

    def union(self, p1:Point, p2: Point):
        a: Point = self.find_set(p1)
        b: Point = self.find_set(p2)
        
        if a==b: 
            return 

        if self.size[a] < self.size[b]:
            a,b = b,a

        self.parents[b] = a 
        self.size[a] += self.size[b]
        self.size[b] = -1
        
        if len([self.size[e] for e in self.size if self.size[e]>0]) == 1:
            print(p1, p2)
            exit(0)





def distance(p1: Point, p2: Point)->float:
    return sqrt((p1[0]-p2[0])**2 + (p1[1]-p2[1])**2 + (p1[2]-p2[2])**2) 

if __name__ == "__main__":
    input = open("inputs/2025/08/input.txt", "r")
    sample = open("inputs/2025/08/sample.txt", "r")
    
    file = input
    points: list[Point] = []
    edges: list[tuple[Point, Point, float]] = []

    for line in file:
        p = [int(e) for e in line.strip().split(",")]
        points.append((p[0], p[1], p[2]))
    
    for i in range(0, len(points)):
        for j in range(i+1, len(points)):
            edges.append((points[i], points[j], distance(points[i], points[j])))
     
    
    edges.sort(key=lambda x: x[2])

    
    finder: DisjointSet = DisjointSet(points)
   
    while True:
        p1,p2,_ = edges.pop(0)
        finder.union(p1, p2)

    sets: list[Point] = sorted(finder.size, reverse=True,key=lambda x: finder.size[x])   
    
    for e in sets[:3]:
        print(e, finder.size[e])
    
