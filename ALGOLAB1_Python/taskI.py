x, y = map(int, input().split())
count = 0
max_len = len(bin(y)[2:])
for i in range(1, max_len):
    for k in range(1, max_len):
        for j in range(1, max_len):
            s = '1' * i + '0' * k + '1' * j
            #print(int(s, 2))
            if x <= int(s, 2) <= y:
                #print(int(s))
                count += 1
print(count)
