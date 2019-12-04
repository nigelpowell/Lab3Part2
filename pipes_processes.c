#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 
  
int main() 
{     
    int first_pipe[2];  // variable declarations
    int second_pipe[2];    
    char fixed_string[] = "howard.edu", fixed_string_2[] = "gobison.org"; 
    char input_string[100]; 
    pid_t p; 
  
    if (pipe(first_pipe)==-1) 
    { 
        fprintf(stderr, "Pipe Failed" ); 
        return 1; 
    } 
    if (pipe(second_pipe)==-1) 
    { 
        fprintf(stderr, "Pipe Failed" ); 
        return 1; 
    } 
  
    printf("Enter a string to concatenate:"); // user prints name
    scanf("%s", input_string); 
    p = fork(); 
  
    if (p < 0) 
    { 
        fprintf(stderr, "fork Failed" ); 
        return 1; 
    } 
  
    else if (p > 0) 
    { 
        char concatenated_string[100];   
        close(first_pipe[0]);  
        write(first_pipe[1], input_string, strlen(input_string)+1); 
        close(first_pipe[1]);  
        wait(NULL);   
        close(second_pipe[1]); 
        read(second_pipe[0], concatenated_string, 100);
        
        int k = strlen(concatenated_string); 
        int i; 
        for (i=0; i<strlen(fixed_string_2); i++) 
           concatenated_string[k++] = fixed_string_2[i]; 
        concatenated_string[k] = '\0';   
        
        printf("Concatenated string %s\n", concatenated_string); // prints what user types
        close(second_pipe[0]); 
    } 
  
    else
    { 
        close(first_pipe[1]);   
        char concatenated_string[100]; 
        read(first_pipe[0], concatenated_string, 100); 
  
        int k = strlen(concatenated_string); 
        int i; 
        for (i=0; i<strlen(fixed_string); i++) 
            concatenated_string[k++] = fixed_string[i]; 
  
        concatenated_string[k] = '\0';   
        close(first_pipe[0]); 
        close(second_pipe[0]);   
        write(second_pipe[1], concatenated_string, strlen(concatenated_string)+1); 
        close(second_pipe[1]);   
        exit(0); 
    } 
} 
