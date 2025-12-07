/*
Implement a function void decodeString(char s[]) which prints the string obtained by replacing each number with 
the same number of occurrences of the letter preceding the number. Leave other characters unchanged.

I.e.: decodeString("gi3G2E2eL3A") should print giiiiGGGEEEeLLLLA
*/

#include <stdio.h>
#include <ctype.h>

#define N 300

char replaced[N]; 

void decodeString(char s[]) {
    int i = 0; // for keeping track of s
    int j = 0; // for replaced string
    char last_char = 0;

    while (s[i] != '\0') {
        if (isdigit(s[i])) 
        {
            int count = 0;

            while (isdigit(s[i])) 
            {
                count = count * 10 + (s[i] - '0');
                i++;
            }

            for (int k = 0; k < count; k++) 
            {
                if (last_char != 0) 
                {
                    if (j < N-1) 
                    { 
                        replaced[j] = last_char;
                        j++;
                    }
                }
            }
        } 
        else if (isalpha(s[i]))
        {
            if (j < N-1) 
            {
                replaced[j] = s[i];
                j++;
            }
            last_char = s[i];
            i++;
        }
    }

    replaced[j] = '\0';

    printf("%s", replaced);
}

int main() {
    char input[] = "gi3G2E2eL3A";
    
    printf("Input:  %s\n", input);
    printf("Output: ");
    
    decodeString(input);
    
    return 0;
}