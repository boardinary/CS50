#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // Error handling
    if (argc < 2)
    {
        printf("missing command line argument\n");
        return 1;
    }
    else if (argc > 2)
    {
        printf("Usage: ./subsitution key\n");
        return 1;
    }
    else if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters\n");
        return 1;
    }

    //
    else if (strlen(argv[1]) == 26)
    {
        char key[26];
        strcpy(key, argv[1]);

        // Check key for invalid characters
        for (int i = 0; i < 26; i++)
        {
            if (key[i] >= 'A' && key[i] <= 'Z')
            {

            }

            else if (key[i] >= 'a' && key[i] <= 'z')
            {

            }

            else
            {
                printf("Key must only contain letters.\n");
                return 1;
            }
        }

        // Check key for duplicate characters

        for (int i = 1; i < 26; i++)
        {
            for (int j = 0; j < i; j++)
            {
                if ((key[i] - key[j]) % 32 == 0)
                {
                    printf("Key must not contain duplicate letters.\n");
                    return 1;
                }
                else
                {

                }
            }
        }

        // Creating cypher string
        string text = get_string("plaintext: ");
        int i;
        int n = strlen(text);
        char cypher[n + 1];

        for (i = 0; i < n; i++)
        {
            // If lowercase letter
            if (text[i] >= 'a' && text[i] <= 'z')
            {
                // Indexing alphabet position
                int index = text[i] - 'a';
                cypher[i] = (key[index] - 'A') % 32 + 'a';
            }
            // If uppercase letter
            else if (text[i] >= 'A' && text[i] <= 'Z')
            {
                // Indexing alphabet position
                int index = text[i] - 'A';
                cypher[i] = (key[index] - 'A') % 32 + 'A';
            }
            // If other symbol
            else
            {
                cypher[i] = text[i];
            }
        }

        //add null terminator
        cypher[i] = '\0';
        printf("ciphertext:  %s\n", cypher);

    }

}


