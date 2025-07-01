import math
inp = input().split(' ')
n = int(inp[0])
k = int(inp[1])
lg = math.log(n, 2)
print("Your wish is granted!" if lg <= k else "You will become a flying monkey!\n")