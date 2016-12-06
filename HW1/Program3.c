/* CS261- HW1 - Program3.c*/
/* Name:  Jordan Gilman
 * Date:  4/01/2016
 * Solution description:  Basically just calls all of the functions setup
 by the template.  'generate' uses the professor's method of generating random
 letters in conjunction with the random time seed create by srand().  For
 discovering the min/max of the scores, I just run through each element once,
 if it is less than the current min it becomes the new min.  The opposite
 process occurs for the max.  During this algorithm, I sum all the elements.
 The complexity of this algorithm is O(n).  At the end the sum is divided
 by the number of scores, typcasted with double to obtain the average score.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct student{
	char initials[2];
	int score;
};

struct student* allocate(){
     /*Allocate memory for ten students*/
     struct student *stud = (struct student*) malloc(10*sizeof(struct student));

     /*return the pointer*/
     return stud;
}

void generate(struct student* students){
     /*Generate random initials and scores for ten students.
	The two initial letters must be capital and must be between A and Z. 
	The scores must be between 0 and 100*/
  int i;
  char c1, c2;

  for(i = 0; i < 10; i++) {
    c1 = rand() % 26 + 'A';
    c2 = rand() % 26 + 'A';

    students[i].initials[0] = c1;
    students[i].initials[1] = c2;
    students[i].score = rand() % 101;
  }
     
}

void output(struct student* students){
     /*Output information about the ten students in the format:
              1. Initials  Score
              2. Initials  Score
              ...
              10. Initials Score*/

    int i;
    for(i = 0; i < 10; i++) {
      printf("%d.\t%c%c\t%d\n", (i + 1), students[i].initials[0],
        students[i].initials[1], students[i].score);
    }
}

void summary(struct student* students){
     /*Compute and print the minimum, maximum and average scores of the ten students*/

    int i;
    int min = 100, max = 0, sum = 0;
    double avg;

    for(i = 0; i < 10; i++){
      if(students[i].score > max)
        max = students[i].score;

      if(students[i].score < min)
        min = students[i].score;

      sum = sum + students[i].score;
    }

    avg = (double) sum / 10;
    printf("Min = %d, Max = %d, Average = %0.2f\n", min, max, avg);
}

void deallocate(struct student* stud){
     /*Deallocate memory from stud*/
    free(stud);
}

int main(){
    struct student* stud = NULL;
    srand((unsigned) time(NULL));
    
    /*call allocate*/
    stud = allocate();
    
    /*call generate*/
    generate(stud);
    
    /*call output*/
    output(stud);

    /*call summary*/
    summary(stud);

    /*call deallocate*/
    deallocate(stud);

    return 0;
}
