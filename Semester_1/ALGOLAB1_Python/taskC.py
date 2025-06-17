def main():
    b, a = map(int, input().split())
    while b != a:
        if b > a:
            b -= a
        else:
            a -= b

    print(b)


if __name__ == "__main__":
    main()
