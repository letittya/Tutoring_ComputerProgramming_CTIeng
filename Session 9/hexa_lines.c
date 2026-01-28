/*
  Read text from standard input line by line. Identify valid hexadecimal numbers (digits 0-9, A-F, a-f).
  A number is valid ONLY if delimited by spaces, newlines, or EOF. The hexadecimal numbers don't have 0x or 0X in front of them.
  
  For each line, print:
  - Count: Number of valid hex numbers.
  - Average: Average decimal value.
  - Max: Maximum decimal value.
  
  Example Input:
  10 A 2
  1A.5 FF
  
  Example Output:
  Line 1: Count=3, Max=16, Avg=9.33
  Line 2: Count=1, Max=255, Avg=255.00  ( 1A.5 is invalid)
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

void print_line_stats(int count, long sum, int max) {
    if (count > 0) {
        printf("Stats: Count=%d, Max=%d, Avg=%.2f\n", count, max, (double)sum / count);
    } else {
        printf("No valid numbers on this line.\n");
    }
}

// state machine

void analyze_text() {
    int c;
    
    // 0 = waiting, 1 = hex, 2 = invalid
    int state = 0; 

    // line stats
    int line_count = 0;
    long line_sum = 0;
    int line_max = -1;

    // current number
    long current_val = 0;

    while ((c = getchar()) != EOF) {
        
        // state 0: waiting (looking for start of a word)
        if (state == 0) {
            if (c == '\n') {
                print_line_stats(line_count, line_sum, line_max);
                line_count = 0; line_sum = 0; line_max = -1;
            } 
            else if (isspace(c)) {
                state = 0; // so basically do nothing 
            }
            else if (get_hex_value(c) != -1) {
                // found a digit! move to hex state
                state = 1;
                current_val = get_hex_value(c);
            } 
            else {
                // found a bad char immediately (like '.')
                state = 2;
            }
        }

        // state 1: hex (building a valid number)
        else if (state == 1) {
            if (c == '\n') {
                // end of word (valid) and end of line
                // 1. update stats
                line_count++;
                line_sum = line_sum + current_val;
                if (current_val > line_max) line_max = current_val;

                // 2. print & reset line
                print_line_stats(line_count, line_sum, line_max);
                line_count = 0; line_sum = 0; line_max = -1;
                
                state = 0; // go back to waiting
            }
            else if (isspace(c)) {
                // end of word (valid)
                line_count++;
                line_sum = line_sum + current_val;
                if (current_val > line_max) line_max = current_val;
                
                state = 0; // go back to waiting
            }
            else if (get_hex_value(c) != -1) {
                // valid digit, keep building
                current_val = (current_val * 16) + get_hex_value(c);
            }
            else {
                // found a bad char inside the number (e.g., '1a.5')
                // the whole number is now trash.
                state = 2; 
            }
        }

        // state 2: invalid (eating garbage until space)
        else if (state == 2) {
            if (c == '\n') {
                // end of line. print what we have (ignoring the bad word)
                print_line_stats(line_count, line_sum, line_max);
                line_count = 0; line_sum = 0; line_max = -1;
                state = 0;
            }
            else if (isspace(c)) {
                // end of the bad word. ready for next one.
                state = 0;
            }
            else {
                state = 2;
                // still inside the bad word, ignore character
            }
        }
    }
}

int main() {
    printf("Enter hex numbers:\n");
    analyze_text();
    return 0;
}