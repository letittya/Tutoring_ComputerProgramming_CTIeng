/*
Implement a program that reads data from a file, specified as a command-line argument.

File Format: student_name grade_average Fields: Separated by one or more spaces. 

Constraints: A student's name is at most 50 characters.
The number of students is unknown (you must handle any number of lines).

Goal: Print the list of students who have a passing grade (average >= 5.00). 
The output must be sorted in descending order of their grade average. Break ties (when the grade is the same) by sorting the names alphabetically.

Requirements:
Use dynamic allocation (malloc, realloc) to store the students. You cannot use a fixed-size array like students[100].
Use the qsort function for sorting.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[51];
    float grade;
} STUDENT;


// comparison function for qsort
int compare_students(const void *a, const void *b) {
    STUDENT *s1 = (STUDENT *)a;
    STUDENT *s2 = (STUDENT *)b;

    // sort grade descending (highest first)
    if (s1->grade > s2->grade) return -1;
    if (s1->grade < s2->grade) return 1;

    // sort name ascending (a-z) if grades are equal
    return strcmp(s1->name, s2->name);
}

// reads students from file into a dynamic array
// returns the array, and updates 'count' via pointer
STUDENT *read_students(FILE *f, int *count) {
    int capacity = 2; 
    *count = 0; // initialize the main variable to 0
    
    // allocate initial memory
    STUDENT *students = malloc(capacity * sizeof(STUDENT));
    if (students == NULL) {
        printf("initial malloc failed");
        exit(1); // exit on error or return 
    }

    // infinite loop - break when reading finishes
    while (1) {
        
        // 1. check capacity before reading
        // note: we access the value using *count
        if (*count >= capacity) {
            capacity = capacity * 2;
            
            STUDENT *ptr = realloc(students, capacity * sizeof(STUDENT));
            
            if (ptr == NULL) {
                printf("realloc failed");
                free(students);
                exit(1);
            }
            students = ptr;
        }

        // 2. read directly into the array
        // if fscanf fails to read 2 items, we stop
        if (fscanf(f, "%50s %f", students[*count].name, &students[*count].grade) != 2) {
            break;
        }

        // 3. increment the counter
        (*count)++;
    }
    
    return students;
}

void print_passing_students(STUDENT *students, int count) {
    printf("passing students (>= 5.00)\n");
    
    int found_any = 0;
    for (int i = 0; i < count; i++) {
        // only print passing grades
        if (students[i].grade >= 5.00) {
            // output format: name : grade
            printf("%s : %.2f\n", students[i].name, students[i].grade);
            found_any = 1;
        }
    }

    if (found_any == 0) {
        printf("no students passed.\n");
    }
}


int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // 1. open
    FILE *f = fopen(argv[1], "r");
    if (f == NULL) {
        printf("error opening file");
        return 1;
    }

    // 2. read
    int count = 0;
    STUDENT *students = read_students(f, &count); 

    // 3. sort
    qsort(students, count, sizeof(STUDENT), compare_students);

    // 4. print
    print_passing_students(students, count);

    // 5. cleanup
    free(students);
    fclose(f);

    return 0;
}