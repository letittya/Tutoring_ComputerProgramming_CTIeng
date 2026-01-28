/*
Task: Write a program which reads, from a file named sample.c, a piece of C source code and sorts the 
lines of the file by line length, ignoring any white-spaces at the beginning of the line.

Primary Sort: Sort by line length (ignoring leading spaces).
Tie-Breaker: If two lines have the same length, place those lines which start with { before other lines.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINES 100
#define MAX_LEN 256


// calc length of line excluding leading whitespace
int getLength(char str[]) {
    int i = 0;
    int len = strlen(str);
    
    // skip spaces at the start
    while (isspace(str[i])) {
        i++;
    }
    
    // length is total length minus skipped spaces
    return len - i;
}

// check if the first non-space character is '{'
int isBrace(char str[]) {
    int i = 0;
    
    // skip spaces 
    while (isspace(str[i])) {
        i++;
    }
    
    // ret 1 (true) if it is a brace, 0 (false) otherwise
    if (str[i] == '{') {
        return 1;
    }
    return 0;
}

// ret the number of lines read
int readLines(FILE *f, char lines[][MAX_LEN], int maxLimit) {
    int count = 0;
    
    // safety check
    if (f == NULL) {
        return 0;
    }
    
    while (count < maxLimit && fgets(lines[count], MAX_LEN, f) != NULL) {
        // ensure every line ends with '\n' to prevent printing issues
        int len = strlen(lines[count]);
        if (len > 0 && lines[count][len - 1] != '\n') {
            lines[count][len] = '\n';
            lines[count][len + 1] = '\0';
        }
        
        count++;
    }
    
    return count;
}

// bubble sort with primary (Length) and secondary (Brace) conditions
void sortLines(char lines[][MAX_LEN], int count) {
    int i, j;
    char temp[MAX_LEN]; // for swaps
    
    for (i = 0; i < count - 1; i++) {
        for (j = 0; j < count - 1 - i; j++) {
            
            int lenA = getLength(lines[j]);
            int lenB = getLength(lines[j+1]);
            int swap = 0; // flag means 0 = No Swap, 1 = Swap
            
            // length sorting
            if (lenA > lenB) {
                swap = 1;
            }
            // equal length
            else if (lenA == lenB) {
                // if neighbor (j+1) has a brace and current (j) doesn't
                if (isBrace(lines[j+1]) && !isBrace(lines[j])) {
                    swap = 1; 
                }
            }
            
            if (swap) {
                strcpy(temp, lines[j]);
                strcpy(lines[j], lines[j+1]);
                strcpy(lines[j+1], temp);
            }
        }
    }
}

void printLines(char lines[][MAX_LEN], int count) {
    int i;
    for (i = 0; i < count; i++) {
        printf("%s", lines[i]);
    }
}


int main() {
    char lines[MAX_LINES][MAX_LEN];
    int count = 0;
    
    // 1. open the file 
    FILE *f = fopen("sample.c", "r");
    
    // 2. check file
    if (f == NULL) {
        printf("Error: Could not open file 'sample.c'.\n");
        return -1;
    }
    
    // 3. pass the open file to the reader
    count = readLines(f, lines, MAX_LINES);
    
    // 4. process and Print
    if (count > 0) {
        
        sortLines(lines, count);

        printLines(lines, count);
    } else {
        printf("File is empty.\n");
    }

     // 5. close file
    fclose(f);
    
    return 0;
}