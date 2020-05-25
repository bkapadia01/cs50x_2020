from cs50 import get_float, get_string, get_int
import math


def main():
    amount = ask_change()
    amount = int(math.ceil(amount * 100))
    print(counter(amount))

# calculate change owed
def ask_change():
    while(True):
        a = get_float("Change Owed: ")
        if a > 0:
            break
    return a

# count the number of coins (quarter,dime, nikle, penny)
def counter(amount):
    count = 0

    while(amount >= 25):
        if (25 % amount == 25):
            # print(f"changes: ", amount)
            count += 1
            amount -= 25
        elif (amount == 25):
            print(f"change: ", amount)
            count += 1
            break

    while (9 < amount < 25):
        if (10 % amount == 10):
            # print(f"changes: ", amount)
            count += 1
            amount -= 10
        elif (amount == 10):
            count += 1
            break

    while (4 < amount < 10):
        if (5 % amount == 5):
            count += 1
            amount -= 5
        elif (amount == 5):
            count += 1
            break

    while (0 < amount < 5):
        if (1 % amount == 1):
            count += 1
            amount -= 1
        elif (amount == 1):
            count += 1
            break

    return count


main()
