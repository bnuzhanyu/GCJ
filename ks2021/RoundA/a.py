
def read_int():
    return int(input())

def read_ints():
    return [int(x) for x in input().split(' ')]

def read_str():
    return input().strip() 

case_num = read_int()
for ca in range(1, case_num+1):
    N, K = read_ints()
    s = input().strip()
    v = 0
    for i in range(N // 2):
        if (s[i] == s[N - i - 1]): v = v + 1
    print("Case #{}: {}".format(ca, abs(v - K)))





