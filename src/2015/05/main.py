#!/usr/bin/python3
import itertools
from more_itertools import windowed, pairwise

def is_nice_string_2(test_string):
    enumerated_pairs = {k: v for k, v in enumerate(pairwise(test_string))}
    sorted_enumerated_pairs = sorted(enumerated_pairs.items(), key=lambda item: item[1])
    pairs_locations = {k: list(map(lambda group: group[0], g))
                       for k, g in itertools.groupby(sorted_enumerated_pairs, key=lambda item: item[1])}

    condition1 = False

    for x in pairs_locations.values():
        if len(x) >= 2:
            for c in itertools.combinations(x, 2):
                if abs(c[0] - c[1]) != 1:
                    condition1 = True

    condition2 = any(lhs == rhs for lhs, _, rhs in windowed(test_string, 3))

    return condition1 and condition2


def check(l: str) -> bool:
    d: dict[str, int] = {}
    last_i: int = 0
    last_v: str = ""

    for i in range(0, len(l)-1):
        if i-1 == last_i and last_v == l[i:i+2]: continue
        d[l[i:i+2]] = d.get(l[i:i+2], 0) +1
        last_i = i
        last_v = l[i:i+2]
    
    for i in range(1, len(l)-1):
        if l[i-1] == l[i+1]:
            return any([e>=2 for e in d.values()]) 

    return False
    return any([e>=2 for e in d.values()]) and any(lhs == rhs for (lhs, _, rhs) in windowed(l, 3))


if __name__ == "__main__":
    nice: int = 0
    with open("inputs/2015/05/input.txt") as file:
        for l in file:
            if  check(l):
                nice +=1


    print(nice)
 

