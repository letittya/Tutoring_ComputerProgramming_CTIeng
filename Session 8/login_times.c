/*
Implement a program that reads data from a file, specified as a command-line argument.

File Format: username, hh, mm
Fields: Separated by a comma.
Spacing: Might have an arbitrary number of spaces in between.
Constraints: A line has a maximum of 100 characters.

Goal: Print the data from the file in descending order of their last login time (hh, mm), breaking ties 
(when the last login time is the same) by username.
*/

#include <stdio.h>
#include <string.h>

// constants
#define MAX_USERS 100
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

// sorts the array directly
void sortUsers(UserLogin users[], int count) {
    int i, j;
    UserLogin temp; 
    
    // Loop 1
    for (i = 0; i < count - 1; i++) {
        
        // Loop 2
        for (j = i + 1; j < count; j++) {
            
            int timeI = calculateMinutes(users[i]); 
            int timeJ = calculateMinutes(users[j]); 
            
            // we want the LATEST time (Biggest Number) at the top.
            // so if (j) is BIGGER than the Current (i), SWAP them.
            
            int shouldSwap = 0;
            
            // 1. Primary Check: Time
            if (timeJ > timeI) {
                shouldSwap = 1;
            }
            // Times are equal -> Check Name (A-Z)
            // if times are equal AND Name J comes BEFORE Name I (smaller), swap.
            else if (timeJ == timeI) {
                 if (strcmp(users[j].username, users[i].username) < 0) {
                     shouldSwap = 1;
                 }
            }
            
            // EXECUTE SWAP
            if (shouldSwap == 1) {
                temp = users[i];
                users[i] = users[j];
                users[j] = temp;
            }
        }
    }
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

    UserLogin users[MAX_USERS];
    int count = 0;

    // 2. open the file
    FILE *f = fopen(argv[1], "r");
    
    if (f == NULL) {
        printf("error opening file.\n");
        return 1;
    }

    // 3. READ USERS
    while (count < MAX_USERS) {
        
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
        sortUsers(users, count);
        printUsers(users, count);
    } else {
        printf("no users found.\n");
    }

     // 4. close the file 
    fclose(f);

    return 0;
}