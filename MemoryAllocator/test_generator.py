# Test generator for MemoryAllocator

from random import randint as rand

# memory = rand(1, 2**31 + 1)
memory = rand(1, 4096)
# requests = rand(1, 10**5)
requests = rand(1, 40)
print(memory, requests)
allocations = []
for i in range(requests):
    znak = rand(0, 1)
    if znak == 0 and len(allocations) > 0:
        ind = rand(0, len(allocations) - 1)
        print(-allocations[ind])
        del allocations[ind]
    else:
        allocations.append(i + 1)
        # print(rand(1, 2**31 + 1))
        print(rand(1, 256))
