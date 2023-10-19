#include<stdio.h>
#include<string.h>

int main(int argc, char *argv[]){
    char *cla;

    do{
        // print the dollar sign to indicate the user to type something
        print_prompt1();

        // use pointer to read command line argument as input
        cla = read_cla();

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
        print("%s", cla);
        free(cla);
    }while(true)
    
    exit(EXIT_SUCCESS);
}


