# TODO
from cs50 import SQL
import sys
import csv

db = SQL("sqlite:///students.db")

if(len(sys.argv) != 2):
    print("python import.py input2")
    sys.exit(1)

with open(sys.argv[1], 'r') as csvfile:
    reader = csv.DictReader(csvfile)
    for row in reader:
        # print(row["name"], row["house"], row["birth"])
        name = row["name"]
        house = row["house"]
        birth = row["birth"]
        splitname = name.split(" ")
        # print(splitname)
        if (len(splitname) == 2):
            first = splitname[0]
            last = splitname[1]
            print(first, last)
            db.execute("INSERT INTO students (first, last, house, birth) VALUES (?,?,?,?)", first, last, house, birth)
        elif(len(splitname) == 3):
            first = splitname[0]
            middle = splitname[1]
            last = splitname[2]
            print(first, middle, last)
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?,?,?,?,?)", first, middle, last, house, birth)
