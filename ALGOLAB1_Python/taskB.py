def main():
    n, k = map(int, input().split())
    array = list(map(int, input().split()))
    if abs(k) >= n:
        k = k % n
    if k < 0:
        k = n - abs(k)
    array = array[-k:] + array[:-k]
    print(" ".join(map(str, array)))

if __name__ == "__main__":
    main()
