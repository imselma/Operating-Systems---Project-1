#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

// 'cp' command
void my_cp(const char *source, const char *destination, int force) {
    FILE *src_file, *dest_file;
    char buffer[1024];
    size_t bytes_read;

    src_file = fopen(source, "rb");
    if (src_file == NULL) {
        perror("Error opening source file");
        return;
    }

    dest_file = fopen(destination, force ? "wb" : "ab");
    if (dest_file == NULL) {
        perror("Error opening destination file");
        fclose(src_file);
        return;
    }

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), src_file)) > 0) {
        fwrite(buffer, 1, bytes_read, dest_file);
    }

    fclose(src_file);
    fclose(dest_file);

    printf("File copied successfully.\n");
}

// 'fortune' command
void my_fortune(int cowsay) {
    FILE *fortune_file;
    char line[1024];

    fortune_file = fopen("/usr/share/games/fortunes/fortunes", "r");
    if (fortune_file == NULL) {
        perror("Error opening fortune file");
        return;
    }

    // Seek a random line
    fseek(fortune_file, 0, SEEK_END);
    long filesize = ftell(fortune_file);
    srand(time(NULL));
    long offset = rand() % filesize;
    fseek(fortune_file, offset, SEEK_SET);

    // Read a line
    if (fgets(line, sizeof(line), fortune_file) != NULL) {
        if (cowsay) {
            printf(" _____\n");
            printf("/ %s /\n", line);
            printf(" ----- \n");
            printf("   \\   ^__^\n");
            printf("    \\  (oo)\\_______\n");
            printf("       (__)\\       )\\/\\\n");
            printf("           ||----w |\n");
            printf("           ||     ||\n");
        } else {
            printf("%s", line);
        }
    }

    fclose(fortune_file);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <command> [arguments]\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "cp") == 0) {
        int force = 0;
        const char *source, *destination;
        for (int i = 2; i < argc; i++) {
            if (strcmp(argv[i], "-f") == 0) {
                force = 1;
            } else if (source == NULL) {
                source = argv[i];
            } else {
                destination = argv[i];
            }
        }
        if (source == NULL || destination == NULL) {
            printf("Usage: %s cp [-f] <source> <destination>\n", argv[0]);
            return EXIT_FAILURE;
        }
        my_cp(source, destination, force);
    } else if (strcmp(argv[1], "fortune") == 0) {
        int cowsay = 0;
        for (int i = 2; i < argc; i++) {
            if (strcmp(argv[i], "-c") == 0) {
                cowsay = 1;
            }
        }
        my_fortune(cowsay);
    } else {
        printf("Unknown command: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

/*
For the cp command, an optional -f flag is added to force overwrite the destination file if it already exists. The usage message reflects this change.

For the fortune command, an optional -c flag is added to display the fortune with a "cowsay" ASCII art representation. If the -c flag is provided, the fortune is displayed with cowsay; otherwise, it's displayed as a regular fortune.
*/