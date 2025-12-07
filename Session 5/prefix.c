/*
Implement a function char *extractPrefix(char *s1, char *s2) which takes two strings and returns another string 
consisting of the longest common prefix of the two initial strings.

I.e.: char s1[]="palindrome"; char s2[]="palisade"; should yield "pal"

*/

#include <stdio.h>
#include <string.h>

#define MAX_PREFIX_LEN 100 

char prefix[MAX_PREFIX_LEN]; 

char *extractPrefix(char s1[], char s2[]) 
{
    int i = 0;
    int max_stop = MAX_PREFIX_LEN - 1; 

    while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i] && i < max_stop)
    {
        prefix[i] = s1[i]; 
        i++;
    }

    prefix[i] = '\0';

    return prefix; 
}

int main() {
    char s1_test[] = "palindrome";
    char s2_test[] = "palisade";
    char s3_test[] = "applepie";
    char s4_test[] = "apply";
    
    char *result1 = extractPrefix(s1_test, s2_test);
    printf("Prefix of '%s' and '%s' is: '%s'\n", s1_test, s2_test, result1); 

    char *result2 = extractPrefix(s3_test, s4_test);
    printf("Prefix of '%s' and '%s' is: '%s'\n", s3_test, s4_test, result2); 

    return 0;
}