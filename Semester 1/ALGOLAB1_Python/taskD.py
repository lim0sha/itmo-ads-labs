def main():
    n, m, q = map(int, input().split())
    a = [[0] * m for _ in range(n)]

    k = 0
    for _ in range(q):
        ep, season = map(int, input().split())
        if a[season - 1][ep - 1] != 1:
            k += 1
            a[season - 1][ep - 1] = 1

    print(n * m - k)
    for i in range(n):
        for j in range(m):
            if a[i][j] != 1:
                print(j + 1, i + 1)

if __name__ == "__main__":
    main()
