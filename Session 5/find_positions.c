/*
Implement a function that receives as arguments a string, an array of integers and its capacity, and 
fills the array with all the positions from the string where a 
digit or a vowel is found, without overflowing the array.

Return the number of elements copied into the array. Also, provide an adequate main() function.
*/

#include <stdio.h>
#include <string.h> // Required for strchr()

int findPositions(char s[], int pos_arr[], int capacity) {
    int count = 0;
    int len = strlen(s);

    for (int i = 0; i < len; i++) {
        
        // Stop if the destination array is full
        if (count >= capacity) {
            break;
        }

        // Check if the character is a Vowel OR a Digit using strchr
        if (strchr("AEIOUaeiou", s[i]) != NULL || strchr("0123456789", s[i]) != NULL) {
            pos_arr[count] = i;
            count++;
        }
    }

    return count;
}

int main() {
    char input_string[] = "A1T2O3P4E51111111"; 
    int positions_array[10];
    int capacity = 10;
    
    int filled_count = findPositions(input_string, positions_array, capacity);

    printf("Input string: %s\n", input_string);
    printf("Capacity: %d\n", capacity);
    printf("Found %d positions:\n", filled_count);

    for (int i = 0; i < filled_count; i++) {
        printf("%d ", positions_array[i]);
    }
    printf("\n");

    return 0;
}