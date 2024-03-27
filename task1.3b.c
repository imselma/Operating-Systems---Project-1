#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include  <unistd.h>

int main(int argc, char *argv[]){

printf("Now you are in execProcess1.c\n");
printf("The PID of this process is: %d\n", getpid());
printf("This process returns the sum of numbers from user input!\n");
int sum=0;
for(int i=1; i<argc; i++){
int number = atoi(argv[i]);
sum+=number;
}
printf("The sum is: %d\n", sum);
}
