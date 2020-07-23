#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main(void)
{
    string s = get_string("Text: ");
    float letters = 0;
    float words = 1;
    float sentence = 0;

    // convert all chart to upper
    for (int i = 0; i < strlen(s); i++)
    {
        char upperChar = toupper(s[i]);
        if (upperChar >= 'A' && upperChar <= 'Z')
        {
            letters += 1;
        }
    }

    // calcualte lenght of each word
    for (int j = 0; j < strlen(s); j++)
    {
        if (s[j] == ' ' && (s[j - 1] != ' ' && s[j + 1] != ' '))
        {
            words += 1;
        }
    }

    // calculate lenght of each sentence
    for (int k = 0; k < strlen(s); k++)
    {
        if (s[k] == '.' || s[k] == '?' || s[k] == '!')
        {
            sentence += 1;
        }
    }
    // use formula to caluclate grade read level
    float L = (letters / words) * 100;
    float S = (sentence / words) * 100;
    int grade = round(0.0588 * L - 0.296 * S - 15.8);
    // printf("letter count: %f\n", letters);
    // printf("words count: %f\n", words);
    // printf("sentence count: %f\n", sentence);
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}