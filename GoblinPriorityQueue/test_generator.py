from random import randint as rand

goblins = rand(3, 7)
count = 2 * goblins
popCount = 0
canBePop = 0
operators = ['+', '*', '-']
_id = 1
actions = []
for i in range(1, count + 1):
    action = rand(0, 2)
    if action == 2:
        if popCount < goblins and canBePop > 0:
            actions.append("-")
            popCount += 1
            canBePop -= 1
        else:
            action = rand(0, 1)
            actions.append(f"{operators[action]} {_id}")
            _id += 1
            canBePop += 1
    else:
        if goblins - popCount == count + 1 - i and canBePop > 0:
            action = 2
            actions.append("-")
            popCount += 1
            canBePop -= 1
        else:
            actions.append(f"{operators[action]} {_id}")
            _id += 1
            canBePop += 1

print(count)
for a in actions:
    print(a)

# from random import randint as rand

# goblins = rand(8, 15)
# operators = ['+', '*', '-']
# _id = 1
# actions = []
# for i in range(1, goblins + 1):
#     actions.append(operators[rand(0, 1)])

# print(goblins * 2)
# _id = 1
# for a in actions:
#     print(f"{a} {_id}")
#     _id += 1
# for i in range(goblins):
#     print("-")
# print()
# print("Done!")
