import sys
from functools import lru_cache

def solve():
    ab = []
    data = sys.stdin.readline().strip().split()
    for i in range(0, len(data) - 2, 2):
        ab.append((int(data[i]), int(data[i+1])))
    c, d = int(data[-2]), int(data[-1])
    
    @lru_cache(None)
    def f(x, y):
        if x <= 0 or y <= 0:
            return d
        res = c
        for a, b in ab:
            res += f(x - a, y - b)
        return res
    
    data = sys.stdin.readline().strip().split()
    for i in range(0, len(data), 2):
        x, y = int(data[i]), int(data[i+1])
        print(f(x, y))
    print()

def main():
    T = int(sys.stdin.readline().strip())
    for _ in range(T):
        solve()

if __name__ == "__main__":
    main()
