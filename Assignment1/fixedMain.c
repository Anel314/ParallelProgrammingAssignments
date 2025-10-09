#include <stdlib.h>
int main(int argc, char *argv[]){

    int ipos, ival;

    //[PROBLEM 1] - INITIALIZE THE DECLARED VARIABLES
    ipos = 0;
    ival = 0;

    int *iarray = (int *) malloc(10*sizeof(int));

    if (argc == 2)
        ival = atoi(argv[1]);

    //[PROBLEM 2] - CHANGED THE CONDITION FROM 'i<=10' to 'i<10' TO RESTRICT ACCESSING UNALLOCATED MEMORY SPACE
    for (int i = 0; i<10; i++){ 
        iarray[i] = ipos; 
    }

    for (int i = 0; i<10; i++){
        if (ival == iarray[i])
            ipos = i;
    }

    //[PROBLEM 3] - FREED THE ALLOCATED MEMORY FOR 'iarray'
    free(iarray);
}