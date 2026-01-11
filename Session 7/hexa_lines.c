/*
  Read text from standard input line by line. Identify valid hexadecimal numbers (digits 0-9, A-F, a-f).
  A number is valid ONLY if delimited by spaces, newlines, or EOF.
  
  For each line, print:
  - Count: Number of valid hex numbers.
  - Average: Average decimal value.
  - Max: Maximum decimal value.
  
  Example Input:
  10 A 2
  1A.5 FF
  
  Example Output:
  Line 1: Count=3, Max=10, Avg=7.33
  Line 2: Count=1, Max=255, Avg=255.00  (Note: 1A.5 is invalid)
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h> 


int get_hex_value(int c) {
    // check if 'c' exists in the string of valid hex digits
    if (strchr("0123456789abcdefABCDEF", c) == NULL) {
        return -1;
    }

    if (isdigit(c)) {
        return c - '0';
    } else {
        // use toupper(c) to capitalize the letters so we have less code to write
        return toupper(c) - 'A' + 10;
    }
}

// current line 
void update_line_stats(int value, int *count, long *sum, int *max) {
    (*count)++;
    *sum = *sum +  value;
    if (value > *max) {
        *max = value;
    }
}

// print stats for the current line and resets counters 
void print_and_reset_line(int *count, long *sum, int *max) {
    if (*count > 0) {
        double avg = (double)(*sum) / (*count);
        printf("Stats: Count=%d, Max=%d, Avg=%.2f\n", *count, *max, avg);
    } else {
        printf("No valid numbers on this line.\n");
    }
    
    // reset
    *count = 0;
    *sum = 0;
    *max = -1;
}

void analyze_text() {
    int c;
    
    // line stats 
    int line_count = 0;
    long line_sum = 0;
    int line_max = -1;

    // word state
    int current_val = 0;
    int is_valid_word = 1; // assume valid until we see a non-hex char
    int has_digits = 0;    // ensures empty strings aren't counted

    while ((c = getchar()) != EOF) {
        
        if (isspace(c)) {
            
            // end of a word. Was it a valid hex number?
            if (has_digits && is_valid_word) {
                update_line_stats(current_val, &line_count, &line_sum, &line_max);
            }

            // reset Word State for the next word
            current_val = 0;
            is_valid_word = 1;
            has_digits = 0;

            // was this specifically a Newline?
            if (c == '\n') {
                print_and_reset_line(&line_count, &line_sum, &line_max);
            }

        } else {
            // we are inside a word. Process the character.
            int val = get_hex_value(c);

            if (val != -1) {
                // It is a valid Hex Digit
                if (is_valid_word) {
                    current_val = current_val * 16 + val;
                    has_digits = 1;
                }
            } else {
                // It is NOT a Hex Digit (e.g., '.', 'Z', '?')
                // This marks the ENTIRE word as invalid.
                is_valid_word = 0;
            }
        }
    }
    
    // Handle EOF case (if file ends without a newline)
    if (has_digits && is_valid_word) {
        update_line_stats(current_val, &line_count, &line_sum, &line_max);
        print_and_reset_line(&line_count, &line_sum, &line_max);
    }
}

int main() {
    printf("Enter text (Ctrl+D to end):\n");
    analyze_text();
    return 0;
}