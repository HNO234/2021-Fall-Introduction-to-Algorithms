import random as r
n = r.randint(3, 1000)
idx = r.randint(0, n - 1)
delta = r.randint(0, 1) * 2 - 1

print(n)
for i in range(n):
    if i == idx:
        print(2 + delta, end = ' ')
    else:
        print(2, end = ' ')
print()
