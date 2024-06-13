def main():
    t = int(input())
    for _ in range(t):
        n = int(input())
        minimum = 15
        maximum = 30
        for _ in range(n):
            q, s = input().split()
            s = int(s)
            if q == ">=" and minimum < s:
                minimum = s
            if q == "<=" and maximum > s:
                maximum = s
            if minimum <= maximum:
                print(minimum)
            else:
                print(-1)

if __name__ == "__main__":
    main()
