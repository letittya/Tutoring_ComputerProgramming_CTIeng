/*
Implement a function int read_ints(char *s, int ints[], int capacity) that extracts valid decimal integers from a 
string s and stores them into an array ints.
A valid integer is defined as a sequence of digits that is strictly delimited by spaces or the boundaries of the string (start/end).

Example: In "1 ana are 12 mere", 1 and 12 are valid.
Example: In "29.5 prune", 29 and 5 are invalid because they touch a dot.

The function should return the number of integers successfully stored. Stop reading if the array capacity is reached. */

#include <stdio.h>
#include <stdlib.h> // for strtol (string to long)
#include <ctype.h>  // for isdigit
#include <stdbool.h>

bool is_valid_delimiter(char c) {
    return (c == ' ' || c == '\0');
}

 // scans string 's', finds integers strictly delimited by spaces/start/end and uses strtol to parse them.
int read_ints(const char *s, int ints[], int capacity) {
    int count = 0;
    char *end_ptr; // point to the character AFTER the number strtol reads
    const char *curr = s;

    // loop until end of string or array is full
    while (*curr != '\0' && count < capacity) {
        
        // check if we found the start of a digit
        if (isdigit(*curr)) {
            
            // nr is valid only if it's at the start of the string or the character before it was a space
            int left_ok=0;
            if((curr == s) || isspace(*(curr - 1)))
                left_ok=1;

            // strtol reads the number and sets 'end_ptr' to the character where it stopped
            long num = strtol(curr, &end_ptr, 10);

            // 'end_ptr' is where strtol stopped. if it stopped at a space or \0, it's good
            // if it stopped at smth else like '.' (29.5), it's invalid
            int right_ok=0;
            if (*end_ptr == '\0' || isspace(*end_ptr))
                right_ok = 1;

            // store result if both boundaries are valid
            if (left_ok && right_ok) {
                ints[count] = (int)num;
                count++;
            }

            // move 'curr' to 'end_ptr' because we have already processed those digits.
            // basically it skips the number we just read.
            if (curr != end_ptr) {
                curr = end_ptr;
            } 

        } else {
            // if it is not a digit, just move to the next character
            curr++;
        }
    }

    return count;
}

int main() {
    char input[] = "1 ana are 12 mere, 29.5 prune si 14 portocale 23";
    int results[10]; // can have max 10 ints
    int count = 0;

    count = read_ints(input, results, 10);

    // Print Results
    printf("In the string: [ %s ] we found %d integers: ", input,count);
    for (int i = 0; i < count; i++) {
        printf("%d ", results[i]);
    }
    printf("\n");

    return 0;
}