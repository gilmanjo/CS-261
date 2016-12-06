/* CS261- HW1 - Program6.c*/
/* Name:  Jordan Gilman
 * Date:  4/8/16
 * Solution description:  I used basic if-statements to check whether
 characters were in the vaid range of alphabetic characters.  I also
 checked that the flag is a valid integer.  If so, the program calls a
 loops of function calls that adds the approraite ASCII values in order
 to convert the case.
 */
 
#include <stdio.h>
#include <stdlib.h>

/*converts ch to upper case, assuming it is in lower case currently*/
char toUpperCase(char ch){
    if(ch >= 'A' && ch <= 'Z')
        return ch;
    else
        return ch-'a'+'A';
}

/*converts ch to lower case, assuming it is in upper case currently*/
char toLowerCase(char ch){
    if(ch >= 'a' && ch <= 'z')
        return ch;
    else
     return ch-'A'+'a';
}

void lowerCase(char* word){
     /* Convert to lower case letters */
    int i;

    for(i = 0; word[i] != '\0' ; i++) {
        if((word[i] >= 'a' && word[i] <= 'z')
            || (word[i] >= 'A' && word[i] <= 'Z'))
            word[i] = toLowerCase(word[i]);

        else {
            printf("Non-alphabetic character found.  Exiting progam.");
            break;
        }
    }
}

void upperCase(char* word){
	/* Convert to upper case letters */
    int i;

    for(i = 0; word[i] != '\0' ; i++) {
        if((word[i] >= 'a' && word[i] <= 'z')
            || (word[i] >= 'A' && word[i] <= 'Z'))
            word[i] = toUpperCase(word[i]);

        else {
            printf("Non-alphabetic character found.  Exiting conversion.");
            break;
        }
    }
}

int main(){
    /* Input a word and flag */
    int flag = 0;
    char word[256];

    printf("Please enter a word\n");
    scanf("%s", word);

    printf("\nWhat would you like to change to?\n[0]\tlowercase\n");
    printf("[1]\tuppercase\n");
    scanf("%d", &flag);

    /* Print the input word and flag */
	printf("\nword:\t%s\nFlag:\t%d\n", word, flag);

    /* Based on the value of flag
	  Call lowerCase()
	  or
	  Call upperCase() */
    if(flag == 0)
        lowerCase(word);

    else if(flag == 1)
        upperCase(word);

    else {
        printf("Invalid flag.  Exiting program.");
        return 0;
    }

    
    /* Print the new word */
	printf("\nNew word:  %s", word);
    
    return 0;
}
