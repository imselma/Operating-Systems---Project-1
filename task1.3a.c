#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
int pid = fork();

if(pid<0){
perror("Fork failed");
exit(1);
}
else if(pid==0){
printf("Hello!\n");
printf("You are in mainProcess.c\n");
printf("This is the child process and the PID is: %d\n", getpid());
char *args[] = {"process2", "10", "30", NULL};
execv("./process2", args);
}
else{
wait(NULL);
printf("Now you are back in the mainProcess.c\n");
printf("This is the parent process and the PID is: %d\n", getpid());
printf("Goodbye!");
}
}

//This program forks a child process in which the "./process2" is run using the execv() system call from the exec() system call family. exec() system call makes a different process, but it will have the same process id as the child proces of "mainProcess1.c".THe "process2" is a program declared in execProcess1.c file taht sums up argument numbers. As a first argument of exacv() we run the "process2" and as a second we take the args[] which will serve as the argv[] array with the name of program and the user input argumnets. When the exec() system call is executed, the program proceeds to the parant process of the mainProcess1.c and prints out the stated values. The child process is the duplicate of the parant process, but in compared to execv() which is a different process with same PID, the chaild has a different PID from parent process.
