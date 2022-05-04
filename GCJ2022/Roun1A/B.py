
def read_int():
    return int(input())

def read_ints():
    return [int(x) for x in input().split(' ')]

import random

def ssplit(nums):
    s1 = 0
    s2 = 0
    v1 = []
    v2 = []
    for x in nums:
        if s1 <= s2:
            s1 = s1 + x
            v1.append(x)
        else:
            s2 = s2 + x
            v2.append(x)
    return v1

case_num = read_int()
for ca in range(case_num):
    n = read_int()
    s = set()
    for i in range(30):
        s.add(1<<i)

    for i in range(70):
        x = random.randint(1, 1000000000)
        while x in s:
            x = random.randint(1, 1000000000)
        s.add(x)
    n1 = [x for x in s]
    print(" ".join([str(x) for x in n1]), flush=True)
    n2 = read_ints()
    nums = n1 + n2
    nums.sort()
    nums.reverse()
    v1 = ssplit(nums)
    print(" ".join([str(x) for x in v1]), flush=True)


