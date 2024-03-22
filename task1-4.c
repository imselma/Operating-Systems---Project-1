#include <stdio.h>

#define RESET   "\x1B[0m"
#define RED     "\x1B[31m"
#define GREEN   "\x1B[32m"
#define YELLOW  "\x1B[33m"
#define BLUE    "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN    "\x1B[36m"
#define WHITE   "\x1B[37m"

int main(int argc, char *argv[]) {
    printf("%sHello, %sWorld!%s\n", RED, GREEN, RESET);
    printf("%sThis text is %syellow%s\n", YELLOW, YELLOW, RESET);
    printf("%sThis text is %sblue%s\n", BLUE, BLUE, RESET);
    printf("%sThis text is %smagenta%s\n", MAGENTA, MAGENTA, RESET);
    printf("%sThis text is %scyan%s\n", CYAN, CYAN, RESET);
    printf("%sThis text is %swhite%s\n", WHITE, WHITE, RESET);
    return 0;
}
/*In this example, we define several color codes using escape sequences for ANSI color codes. 
We can then use these codes in printf() statements to add color to our text output.
Additionally, to add a name to our shell program, we can simply specify the name of the executable when we compile the program. 
For example, if we save the above program as myshell.c, we can compile it using the following command:
gcc -o myshell myshell.c
This will create an executable file named myshell, which we can then run using the following command:
./myshell
*/