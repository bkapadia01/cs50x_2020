from cs50 import get_string
import re


def main():
    word = get_string("Text:")
    listWord = numberWords(word)
    Sentences = numberSentence(word)
    Words = len(listWord)
    Letters = letterCount(word)
    L = (Letters/Words)*100
    S = (Sentences/Words)*100
    grade = calculate(L, S)
    
    if (0 < grade <= 16):
        print("Grade:", grade)
    elif(grade < 1):
        print("Before Grade 1")
    elif(grade > 16):
        print("Grade 16+")
    
    # print(Words)
    # print(Letters)
    # print(Sentences)
    # print(grade)


def numberWords(word):
    words = list(map(len, word.split()))
    return words
    

def numberSentence(word):
    split = re.split('(?<!\w\.\w.)(?<![A-Z][a-z]\.)(?<=\.|\?|\!)\s', word)
    S = len(split)
    return S
    

def letterCount(L):
    letters = sum(c.isalpha() for c in L)
    return letters
    

def calculate(L, S):
    grade = round(0.0588 * L - 0.296 * S - 15.8)
    # print("grade::: ", grade)
    return grade


main()
