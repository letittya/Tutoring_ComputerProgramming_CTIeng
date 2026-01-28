/*
Implement a program that reads data from a file, specified as a command-line argument.

File Format: username, hh, mm
Fields: Separated by a comma.
Spacing: Might have an arbitrary number of spaces in between.
Constraints: A line has a maximum of 100 characters.

Goal: Print the data from the file in descending order of their last login time (hh, mm), breaking ties 
(when the last login time is the same) by username.

Solve it using dynamic allocation and qsort function. 
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h> // added for malloc/realloc/free and qsort

// constants
#define MAX_NAME_LEN 101

// structure definition
typedef struct {
    char username[MAX_NAME_LEN];
    int hh;
    int mm;
} UserLogin;

// calculates total minutes for easy comparison
int calculateMinutes(UserLogin user) {
    return (user.hh * 60) + user.mm;
}

// sorts the array through qsort
int compareUsers(const void *a, const void *b) {
    // 1. cast generic void pointers to the type we need
    UserLogin *u1 = (UserLogin *)a;
    UserLogin *u2 = (UserLogin *)b;

    // 2. get the values we need to compare
    // calculateMinutes expects a struct, so we dereference (*u1)
    int time1 = calculateMinutes(*u1);
    int time2 = calculateMinutes(*u2);

    // 3. primary Sort: by TIME (Descending - Big numbers first)
    if (time1 > time2) return -1; // time1 is bigger, so it comes FIRST
    if (time1 < time2) return 1;  // time1 is smaller, so it comes AFTER

    // 4. secondary Sort: NAME 
    // strcmp returns negative 
    return strcmp(u2->username, u1->username);
}

// prints the list
void printUsers(UserLogin users[], int count) {
    int i;
    for (i = 0; i < count; i++) {
        printf("%s, %d, %d\n", users[i].username, users[i].hh, users[i].mm);
    }
}

int main(int argc, char *argv[]) {
    // 1. check arguments
    if (argc != 2) {
        printf(" Input %s and then <filename>\n", argv[0]);
        return 1;
    }

    // MALLOC: Initial allocation for the array (start with a small capacity) [cite: 3]
    int capacity = 2;
    UserLogin *users = malloc(capacity * sizeof(UserLogin));
    if (users == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    int count = 0;

    // 2. open the file
    FILE *f = fopen(argv[1], "r");
    
    if (f == NULL) {
        printf("error opening file.\n");
        free(users);
        return 1;
    }

    // 3. READ USERS
    while (1) { // loop runs until file end, handling size dynamically 
        
        // REALLOC: Check if we need more space before reading 
        if (count >= capacity) {
            capacity = capacity * 2; // double the capacity
            //printf("We did a realloc here \n");
            UserLogin *temp = realloc(users, capacity * sizeof(UserLogin));
            if (temp == NULL) {
                printf("Memory reallocation failed\n");
                break; // or handle error appropriately or return 
            }
            users = temp;
        }

        // attempt to read
        int result = fscanf(f, " %100[^,], %d, %d", users[count].username, &users[count].hh, &users[count].mm);
        
        // did we successfully find exactly 3 items?
        if (result == 3) {
            count++; // yes! Accept this user and move to the next slot
        } else {
            break;   // no! We hit the end of the file (or an error). Stop loop.
        }
    }

    if (count > 0) {
        // QSORT arguments: Array, Number of items, Size of one item, Comparison Logic
        qsort(users, count, sizeof(UserLogin), compareUsers);
        printUsers(users, count);
    } else {
        printf("no users found.\n");
    }

     // 4. close the file 
    fclose(f);
    // 5. free the allocated memory 
    free(users);

    return 0;
}
