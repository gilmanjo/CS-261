












 
    
    
    
     
     
              ...
              1. Initials  Score
              10. Initials Score*/
              2. Initials  Score
     /*Allocate memory for ten students*/
     /*Compute and print the minimum, maximum and average scores of the ten students*/
     /*Deallocate memory from stud*/
     /*Generate random initials and scores for ten students.
     /*Output information about the ten students in the format:
     /*return the pointer*/
     return stud;
     struct student *stud = (struct student*) malloc(10*sizeof(struct student));
    /*call allocate*/
    /*call deallocate*/
    /*call generate*/
    /*call output*/
    /*call summary*/
    c1 = rand() % 26 + 'A';
    c2 = rand() % 26 + 'A';
    deallocate(stud);
    free(stud);
    generate(stud);
    output(stud);
    return 0;
    struct student* stud = NULL;
    stud = allocate();
    stud[i]->
    stud[i]->initials[0] = c1;
    summary(stud);
  char c1, c2;
  char initials[2];
  for(i = 0; i < 10; i++) {
  int i;
  int score;
  The scores must be between 0 and 100*/
  The two initial letters must be capital and must be between A and Z. 
  }
 * Date:
 * Solution description:
 */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
/* CS261- HW1 - Program3.c*/
/* Name:
int main(){
struct student* allocate(){
struct student{
void deallocate(struct student* stud){
void generate(struct student* students){
void output(struct student* students){
void summary(struct student* students){
}
}
}
}
}
}
};