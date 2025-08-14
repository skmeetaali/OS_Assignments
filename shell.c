#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
extern char **environ;
#define ARGC 20
int main() {


          char * username = getlogin();
//        char  * usr;
      //  &usr = strcat( "/home/", username );        
 //       printf("%s", usr);
        
        
        while(1) {
                // current working directory
                char dir[256], *cwd;
                size_t size = 256;
                cwd = getcwd(dir, size);
                printf("%s",cwd);
        
        
               
                // getting input line from user using getline
                size_t n;
                n = 200;
                char * argv;
                argv = (char *)malloc(sizeof(char)*n);
                if( getline(&argv, &n, stdin) == -1 ) {
                        printf("\n");
                        return 0;
                }
                argv[strcspn(argv, "\n")] = '\0';  // remove newline


                // breaking the input line into tokens
                char * delim = " ";
                char * token;
                char * arg[ARGC];
                int i = 0;
                token = strtok(argv, delim);
                arg[i] = token; 
                while(token) {
                token = strtok(NULL, delim);
                arg[++i] = token;
                }    
                
                // exit code
                if( strcmp(arg[0], "exit" ) == 0 ) {
                        return 0;
                }
        

              
                // cd command
                if( strcmp(arg[0], "cd") == 0 ) {
                
                        if( strcmp( arg[1], "") == 0 );
                        
                        // cd ~ change to home directory
                    /*    else if( strcmp( arg[1], "~" ) == 0 ) { 
                                char * username = getlogin();
                                if( chdir( username ) != 0 ) {
                                        perror("can't change directory");
                                } 
                        } */
                        
                        else if( chdir(arg[1]) != 0 ) {
                                perror("can't change directory");                              
                        }

                }
                
                

                
   
                // creating a new process 
                int pid;
                pid = fork();
                if( pid == 0) {     
                
                        // if arg[0] == cd
                        if( strcmp( arg[0], "cd" ) == 0 ) {
                                return 0;
                        }
                                
                        
                        // passing the tokens to exec
                        if( execvp(arg[0], arg) == -1 ) {
                                perror("execvp failed :");
                        }

                }
                else{
                        wait(0);
                }
                
        }
        return 0;
}

