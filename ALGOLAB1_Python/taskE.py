def main():
    n = int(input())
    a = input().split()
    i = 0
    mist = 0
    while i < (n // 2):
        if a[i] != a[n - i - 1] and mist == 0:
            mist += 1
        if mist == 1:
            if a[i] != a[n - i - 2] and a[i + 1] != a[n - i - 1]:
                mist += 1
        if mist == 2:
            break
        i += 1

    if mist == 2:
        print("NO")
    else:
        print("YES")


if __name__ == "__main__":
    main()
