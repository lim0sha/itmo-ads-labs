n = int(input())
total = -1

count_added = 0
array = list(map(int, input().split()))
new_array = list()

for i in range(0, 3):
    new_array += array
    count_added += 1
# print(new_array)

s = new_array[0]
for i in range(n * count_added):
    if (s & new_array[i]) != 0:
        s = new_array[i]
        total += 1
    else:
        s = s | new_array[i]
# print(s, total)

if total == 0:
    print(1)
else:
    print((total + count_added - 1) // count_added)
