#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGS 64

// Function to display the prompt
void display_prompt() {
    printf("prompt$ ");
}

// Function to parse input into arguments
void parse_input(char *input, char **args) {
    char *token;
    int i = 0;

    token = strtok(input, " \t\n");
    while (token != NULL && i < MAX_ARGS - 1) {
        args[i++] = token;
        token = strtok(NULL, " \t\n");
    }
    args[i] = NULL;
}

// Built-in function to exit the shell
void exit_shell() {
    printf("Exiting shell...\n");
    exit(EXIT_SUCCESS);
}

// Function to execute external commands
void execute_command(char **args) {
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0) {
        // Child process
        if (execvp(args[0], args) == -1) {
            perror("execvp");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        // Error forking
        perror("fork");
    } else {
        // Parent process
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}

int main() {
    char input[MAX_COMMAND_LENGTH];
    char *args[MAX_ARGS];

    while (1) {
        display_prompt();
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }

        // Remove trailing newline
        input[strcspn(input, "\n")] = 0;

        parse_input(input, args);

        if (args[0] != NULL) {
            if (strcmp(args[0], "exit") == 0) {
                exit_shell();
            } else {
                execute_command(args);
            }
        }
    }

    return 0;
}
