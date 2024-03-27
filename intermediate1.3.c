#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>


int main(){

int pid;

int fd;
int wb;

//Opening file in the parent process and than we  will write to it in both child and parent process
fd=open("intermediateTextFIle.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
printf("Writing into file...\n");

pid = fork();
if(pid<0){
perror("Fork failed");
exit(1);
}else if (pid==0){
//write into file
char message[]="This content of file 'intermediateTextFile.txt' is displayed using execlp().\n";
wb=write(fd, message, sizeof(message)-1);
if(wb<0){
perror("Writing into fail has failed");
exit(1);
}else{
printf("Writing into file is succesfull.\n");
close(fd);
}
}else{
wait(NULL);
printf("You are now in the parent process of intermediate1.3.c, and it will read content from text file 'intermediateTextFile.txt' using execlp() system call.\n");
execlp("cat", "cat", "intermediateTextFIle.txt", NULL);
}
}
//This program in parent process opens a file using open() and forks a child process. In the child process we write a message in the file using write(). When the execution of file process finishes, it returns back to the parent process and calls the execlp() system call. THe execlp() system call is used to execute files and it creates a new different process that will display the content of text file with the cat command that displays the content of file.
