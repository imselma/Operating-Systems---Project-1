#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

// 'cp' command
void my_cp(const char *source, const char *destination) {
    FILE *src_file, *dest_file;
    char buffer[1024];
    size_t bytes_read;

    src_file = fopen(source, "rb");
    if (src_file == NULL) {
        perror("Error opening source file");
        return;
    }

    dest_file = fopen(destination, "wb");
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

// 'history' command
void my_history() {
    system("history");
}

// 'free' command
void my_free() {
    system("free");
}

//'fortune' command
void my_fortune() {
    system("fortune");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <command> [arguments]\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "cp") == 0) {
        if (argc != 4) {
            printf("Usage: %s cp <source> <destination>\n", argv[0]);
            return EXIT_FAILURE;
        }
        my_cp(argv[2], argv[3]);
    } else if (strcmp(argv[1], "history") == 0) {
        my_history();
    } else if (strcmp(argv[1], "free") == 0) {
        my_free();
    } else if (strcmp(argv[1], "fortune") == 0) {
        my_fortune();
    } else {
        printf("Unknown command: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
