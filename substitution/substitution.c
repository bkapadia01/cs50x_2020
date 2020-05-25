#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    string key = argv[1];

    if (argc != 2)
    {
        printf("missing command-line argument\n");
        return 1;
    }
    if (strlen(key) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    for (int i = 0; i < 26; i++)
    {
        if (!isalpha(key[i]))
        {
            printf("Key must only include alphabetic characters\n");
            return 1;
        }
    }
    for (int i = 0; i < strlen(key) - 1; i++)
    {
        if (!isalpha(key[i]))
        {
            printf("Key must only include alphabetic characters\n");
            return 1;
        }
        for (int j = i + 1; j < strlen(key); j++)
        {
            if (key[i] == key[j])
            {
                printf("The charcters in the key are not unique %c\n", key[i]);
                return 1;
            }
        }
    }

    string text = get_string("plaintext: ");
    printf("ciphertext: ");

    for (int i = 0; i < strlen(text); i++)
    {
        if (isupper(text[i]))
        {
            printf("%c", toupper(key[i + (text[i] - 65 - i)]));
        }
        else if (islower(text[i]))
        {
            printf("%c", tolower(key[i + (text[i] - 97 - i)]));
        }

        else if (islower(text[i]) && islower(key[i]))
        {
            printf("%c", key[i + (text[i] - 97 - i)]);
        }
        else if (isupper(text[i]) && isupper(key[i]))
        {
            printf("%c", key[i + (text[i] - 65 - i)]);
        }
        else if (!isalpha(text[i]))
        {
            printf("%c", text[i]);
        }
    }
    printf("\n");
    return 0;
}