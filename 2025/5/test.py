import re

ranges = open("input.txt").read()
ranges = [(int(a), int(b)) for a, b in re.findall(r"(\d+)-(\d+)", ranges)]

def union(I, others):
    a, b = I
    rest = []
    while others:
        c, d = J = others.pop()
        if b < c or a > d:
            rest.append(J)
        else:
            a, b = min(a, c), max(b, d)
            others += rest
            rest = []
    return (a, b), rest

disjoint = []
while ranges:
    I, ranges = union(ranges.pop(), ranges)
    disjoint.append(I)

p2 = sum(b - a + 1 for a, b in disjoint)

print(p2)
