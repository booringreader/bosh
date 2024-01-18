#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>
#include "../shell/shell.h" // prompt
#include "executor.h"
#include "../node/node.h" // has AST structure
#include <sys/stat.h> // contains func for file info and status (strictly for system calls)
#include <sys/wait.h> // func. for process management

/*
* step1 : function to search passed command's executable
        i- get values of PATH variable
        ii- check for pointer validity & PATH variable for NULL values
        iii- pull out each directory using pointer tracking (PATH values are stored in contiguous memory blocks
        iv- make the devise the location value of each file using a 'path' array containing directory and file info
        v- check for the corresponding file executable in the path
            a- use stat() func. and structure; to check if the file is in the structure
        vi- perform furthur checks using macros for the type and mdoe of file
        vii- then return the path value if every check is passed
* step3 : function to execute command line input
        i- if the input command has '/' then it will be treated as path and directly passed into execv()
            a- execv(path to the executable, array of strings (pointer to command)
        ii- if '/' is not in command then search_path is passed to retrieve the path string
* step4 : function to free memory allocated to each string (inside pointer array argv) assuming it was allocated dynamically
        i- the memory allocated to the array itself is not freed yet
* step5 : main function of the executor
        i-exception handling for structure existence
        ii- out the root node (node passed) of AST pull out the command(first child)
        iii- 
*/

char *search_path(char *file){ // func. that takes char and returns a pointer to char
    char *PATH = getenv("PATH"); // to track the path variable all the times (p and p2 will be used for other purposes too)
    char *p = PATH; // to track the beginning of a new directory path
    char *p2; // to track the end of the directory path

    while(p && *p){ // p checks for NULL pointer & *p for the NULL in PATH
       p2 = p; // same starting point
       while(*p2 && *p2 != ':'){ // if p2 is not NULL and the corresponding value is not : (since this marks the end of directory)
       // using *p2 insted of p2 to track the end of PATH simultaeneously
            p2++; // keep moving to the succeeding chars
        }
        int plen = p2-p; // length of the directory path
        if(!plen){ // if length of directory path is 0, then
            plen = 1; // assign one byte for the NULL character
        }

        int alen= strlen(file);
        int path[plen+1/*for '/' */+alen+1/*for '\0'*/];
       strncpy(path, p, p2-p); // copy specific length of string to array (source, dest, len)

       // pulled out the directory name from PATH variable and copied it into an array to perform operations using it
       // now we can work on marinating the file executable by joining the path of directory with the file name; this is assuming that the directory has the corresponding executable surely. e.g. /usr/bin + /file_name

       //first we perform checks on the file, for this first get the information on the file using sys/stat header file functionalities
        if(p2[-1] != '/'){ //checks whether the previous char to p2 is a / or not; p2[0] denotes the current memory address pointer is on
            strcat(path, '/'); // appends / to path after directory
        }
        path[p2-p] = '\0'; // adds null to mark the end of string
        strcat(path,file); // concatenate file name at the end

        // now we use stat() to retrieve info about the file and perform some checks on it

        struct stat st;
        if(stat(path, &st)==0){ // if copy op success
            if(!S_ISREG(st.st_mode)){ //using macro to perform regular file check
                errno = ENOENT; // no such file
                p=p2; // move the pointer p forward
                if(*p2 == ':'){
                    p++;  // not p2, since they are still at the :, p must move one step forward 
                }
                continue; // exists this if block
            }
            *p = malloc(strlen(path)+1); // path array is local, dynamic allocation ensures that array data exists after function termination
            if(!p){
                return NULL;
            }
            strcpy(p, path); 
            return p;
        }else{ //file info couldn't be stored in struct or in our case - since we're assuming that the file has permissions needed and the file exits surely - file not found
            p = p2;
            if(*p2==':'){
                p++;
            }
        }
    }
    errno = ENOENT;  // while loop checks whether the PATH values exist && whether the pointer is dangling
    return NULL; 
}

int do_exec_cmd(int *argc, char **argv){ //pointer to array argv
    if(strchr(argv[0], '/')){ // if there is '/' in the first string
        execv(argv[0], argv);
    }     // execv() to replace current process (OS) with other
    else{
        char *path = search_path(argv[0]);
        if(!path){
            return 0;
        }
        execv(path, argv);
        free(path); // dynamically allocated but not freed in search_path()
    }
    return 0;
}

