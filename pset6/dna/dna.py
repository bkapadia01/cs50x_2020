import sys
import csv
import re
from collections import Counter


if(len(sys.argv) != 3):
    print("Usuage: python dna.py data.csv sequence.txt")
    sys.exit(1)

database = sys.argv[1]
sequence = sys.argv[2]
array = []
sequenceFile = open(f'{sequence}', 'r')
dictionary_array2d = []
dictionary = []

# find matching dna sequence max number of repeats
def findmatchingmax(strsqn, dna):
    matches = re.finditer(r'(%s)+' % strsqn, dna, re.MULTILINE)
    longest_match = ''
    for match_count, match in enumerate(matches, start=1):
        if len(match.group(0)) > len(longest_match):
            longest_match = match.group(0)
    return longest_match.count(strsqn)

# find all mathcing dna sequence
def arrayMatch(sequenceFile):
    for c in sequenceFile:
        # print(c)
        for sqn in header:
            find = findmatchingmax(sqn, c)
            # find = re.findall(sqn , c)
            # find = re.findall(r'(%s)*' % sqn , c)
            # print(find)
            array.append(find)
        # print(array)
        return array

# match dna sequence with person
def nameMatch(dictionary_array2d):
    for i, sequence in enumerate(dictionary_array2d):
        if(sequence == array):
            return dictionary[i][0]


with open(f'{database}', 'r') as databaseFile:
    # print(databaseFile.read())
    db_dict = csv.DictReader(databaseFile)
    header = db_dict.fieldnames[1:]
    # print(header)
    for row in db_dict:
        # print(row)
        test = row.values()
        dictionary.append(list(test))
        vals = list(test)[1:]
        arrs = map(int, vals)
        indiv = []
        for arr in arrs:
            indiv.append(arr)
        # print(indiv)
        dictionary_array2d.append(indiv)

    arrayMatcher = arrayMatch(sequenceFile)
    # print(arrayMatcher)
    nameMatcher = nameMatch(dictionary_array2d)

    if(nameMatcher == None):
        print("No match")
    else:
        print(nameMatcher)
