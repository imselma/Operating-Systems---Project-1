#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]){

int pid;

while(1){
pid=fork();
if(pid<0){
perror("Fork failed.\n");
exit(1);
}else if(pid==0){
printf("I'm a fork bomb!\n");
}else{
printf("Hello from parent!\n");
}
}
}

//This would be an example of a fork bomb. When the program is compiled (gcc -WAll -o additionally additionally1.3.c) and executed (./addirionally) it would  continiously fork new processes because of the infinite loop (while(1)).
//Because of the infinite creation of new processes, it will very fast consume all system resources, causing the system to crash and not be resposive anymore. That's why are forkbomb extremely dangerous to implement on real operating systems, and can be very harmful when created by accident. 
