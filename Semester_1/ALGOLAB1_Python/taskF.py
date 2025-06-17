def main():
    n = int(input())
    numbers = list(map(int, input().split()))

    main_sum = sum(numbers)

    sums_left = 0
    sums_right = main_sum

    for i in range(n):
        if i == 0:
            sums_left = 0
            sums_right = main_sum - numbers[i]
        elif i == n - 1:
            sums_left = main_sum - numbers[i]
            sums_right = 0
        else:
            sums_left += numbers[i - 1]
            sums_right -= numbers[i]

        if sums_left == sums_right:
            print(i)
            return

    print(-1)

if __name__ == "__main__":
    main()
