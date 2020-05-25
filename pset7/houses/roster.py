# TODO
from cs50 import SQL
import sys
import csv

db = SQL("sqlite:///students.db")

if(len(sys.argv) != 2):
    print("python import.py input2")
    sys.exit(1)

house = sys.argv[1]

list = db.execute("SELECT * FROM students WHERE house LIKE (?) ORDER BY last,first ASC", house)


for row in list:
    first = row["first"]
    middle = row["middle"]
    last = row["last"]
    birth = row["birth"]
    
    if row["middle"] == None:
        print(f"{first} {last}, born {birth}")
    else:
        print(f"{first} {middle} {last}, born {birth}")
