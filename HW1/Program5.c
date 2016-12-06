/* CS261- HW1 - Program5.c*/
/* Name:  Jordan Gilman
 * Date:  04/04/2016
 * Solution description:  Most of the code here is all the same
 */
 
#include <stdio.h>
#include <stdlib.h>

struct student{
	char initials[2];
	int score;
};

void sort(struct student* students, int n){
     /*Sort the n students based on their initials*/
     int i;
     for(i = 0; i < n; i++) {
        int j;
       for(j = 0; j < n - 1; j++) {
        if(students[j].initials[0] > students[j + 1].initials[0]
            || (students[j].initials[0] == students[j + 1].initials[0]
            && students[j].initials[1] > students[j + 1].initials[1])) {
            char temp1 = students[j + 1].initials[0];
            char temp2 = students[j + 1].initials[1];
            int temp3 = students[j + 1].score;
            students[j + 1].initials[0] = students[j].initials[0];
            students[j + 1].initials[1] = students[j].initials[1];
            students[j + 1].score = students[j].score;
            students[j].initials[0] = temp1;
            students[j].initials[1] = temp2;
            students[j].score = temp3;
        }
       }
     }   
}

int main(){
    srand((unsigned) time(NULL));
    /*Declare an integer n and assign it a value.*/
    int n = 200;
    int i;
    char c1, c2;

    /*Allocate memory for n students using malloc.*/
    struct student *students = (struct student*) malloc(n*sizeof(struct student));

    /*Generate random IDs and scores for the n students, using rand().*/
    for(i = 0; i < n; i++) {
    c1 = rand() % 26 + 'A';
    c2 = rand() % 26 + 'A';

    students[i].initials[0] = c1;
    students[i].initials[1] = c2;
    students[i].score = rand() % 101;
    }

    /*Print the contents of the array of n students.*/
    printf("Unsorted:\n");
    for(i = 0; i < n; i++) {
      printf("%d.\t%c%c\t%d\n", (i + 1), students[i].initials[0],
        students[i].initials[1], students[i].score);
    }

    /*Pass this array along with n to the sort() function*/
    sort(students, n);

    /*Print the contents of the array of n students.*/
    printf("Sorted:\n");
    for(i = 0; i < n; i++) {
      printf("%d.\t%c%c\t%d\n", (i + 1), students[i].initials[0],
        students[i].initials[1], students[i].score);
    }

    return 0;
}
