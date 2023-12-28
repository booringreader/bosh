#include<stdio.h>
#include<string.h>
// custom header file to link all others
#include "shell.h"
#include<stdlib.h>
#include<errno.h>
#define true 1

int main(int argc, char *argv[]){
    char *cla;

    do{
        // print the dollar sign to indicate the user to type something
       // use pointer to read command line argument as input
        print_prompt1();

        cla = read_cla();
        // possibilities in reading input and corresponding responses

        // if error in reading input, exit
        if(!cla){
            exit(EXIT_SUCCESS);
        }

        // if first character is NULL or the user has pressed enter at any point
        if(cla[0]=='\0' || strcmp(cla, "\n") == 0){
            free(cla);
            continue;
        }
        
        // if pointer reads exit from command line, exit
        if(strcmp(cla, "exit\n") == 0){
            free(cla);
            exit(EXIT_SUCCESS);
        }
        // print whatever the input argument was
        printf("%s", cla);
        free(cla);
    }while(true);
    
    exit(EXIT_SUCCESS);
}

char *read_cla(void){
    //to read input in chunks of 1024 bytes
    char buf[1024];
    char *ptr = NULL;
    int ptrlen = 0;
    
    /* use a while loop to execute code til input is available
    * fgets is used to read input from the standard input i.e keyboard
    */
    while(fgets(buf, 1024, stdin)){
        /* reclare a variable to allocate and reallocate memory on the system
           based on the size of input
        */
        
        //bufferlen does not count null character at the end of buf
        int bufferlen = strlen(buf);
        
        if(!ptr){
            ptr = malloc(bufferlen+1);
        }else{
        /* if the ptr is already pointing towards some previous input, then 
        * create a new pointer which allocates ptr additional memory 
        */
            char *ptr2 = realloc(ptr, ptrlen+bufferlen+1);

            /*
            * next step is to redirect pointer ptr towards the direction ptr2
            * before that we need to make sure that ptr2 is pointing towards 
            something and isn't a null pointer or maybe a victim of some error*/

            /*
            *if(ptr2) means that realloc successfully allocated a memory block
            * and returned a pointer to that block by the name of ptr2
            */
            if(ptr2){
                ptr = ptr2;
            }else{
                free(ptr);
                ptr = NULL;
            }
        }
        /* pointer ptr2 has a short life, long enough to reallocate memory to ptr
        *, ptr has a long life, and it has to be pointing towards a memory block all
        * the time (when there is no error), if the ptr is not pointing towards a 
        * memory block then either it is the first input (we have already dealt with
        * that scenario with the malloc function), or there was some error in
        * reallocating the memory; in this case we need to give out an error to
        * inform the user what has happened
        */
        if(!ptr){
            fprintf(stderr, "memory reallocation failed with error: %s\n", strerror(errno));
            return NULL;
        }
        // till now we have taken all the measures to make sure that the ptr is working correctly, without any errors, now we can copy the input from the buffer to allocated memory
        strcpy(ptr+ptrlen, buf);
    
        if(buf[bufferlen-1] == '\n'){
            if(buf[bufferlen-2] != '\\' || bufferlen == 1){
                return ptr;
            }
            //bufferlen is the length of the new input
            // ptrlen is the length of the already stored input (i.e previous input)
            // the next line of code tells the compiler to shift the null character 2 places advance, this way we remove the backslash(\) and newline character(\n) and cont.
            ptr[ptrlen+bufferlen-2] = '\0';
            //next line reduces the length of the new input by two, since we are not considering the backslash and newline, they were only meant to be indicators
            bufferlen = bufferlen-2;
            print_prompt2();
            
        }
        /*we check to see if the input we’ve got in the buffer ends with \n and, if so, if the \n is escaped by a backslash
        * character \\. If the last \n is not escaped, the input line is complete and we return it to the main() function.
        * Otherwise, we remove the two characters (\\ and \n), print out PS2, and continue reading input.
        */
        ptrlen += bufferlen;
    }   
    return ptr;
}   

