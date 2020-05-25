from cs50 import get_string, get_int


def main():
    h = get_height()
    print_stairs(h)


def get_height():
    while(True):
        height = get_int("Height: ")
        if 0 < height < 9:
            break
    return height


def print_stairs(h):
    for i in range(h):
        for k in range(h - (i + 1), 0, -1):
            print(' ', end="")
        for j in range((h - i - 1), h):
            print('#', end="")
        print('  ', end="")
        for l in range((h - i - 1), h):
            print("#", end="")
        print()


main()
        