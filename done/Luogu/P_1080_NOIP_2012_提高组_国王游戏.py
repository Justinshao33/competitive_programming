import sys
sys.setrecursionlimit(100000)
def solve():
    inp = sys.stdin.read().split()
    it = iter(inp)
    n = int(next(it))
    pro = int(next(it))
    int(next(it)) 
    A = []
    for _ in range(n):
        a = int(next(it))
        b = int(next(it))
        A.append((a, b))
    A.sort(key = lambda x : x[0] * x[1])
    ans = 0
    for a, b in A:
        ans = max(ans, pro // b)
        pro *= a        
    print(ans)

solve()