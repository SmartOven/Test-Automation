# Test generator for Petya Cars task

from random import randint as rand

# n = rand(5, 100000)
n = rand(5, 10)
k = rand(1, n)
# p = rand(5, 500000)
p = rand(5, 12)
print(n, k, p)
for i in range(p):
    print(rand(1, n))
