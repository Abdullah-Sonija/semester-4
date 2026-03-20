#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

#define FIFO_NAME "/tmp/myfifo"
#define BUFFER_SIZE 256

int main() {
    int fd;
    char buffer[BUFFER_SIZE];

    // Create the FIFO (named pipe) if it doesn't exist
    mkfifo(FIFO_NAME, 0666);

    // Open the FIFO for writing
    fd = open(FIFO_NAME, O_WRONLY);
    if (fd == -1) {
        perror("Failed to open FIFO");
        return 1;
    }

    while (1) {
        // Prompt for user input
        printf("Sender: Enter a message (or 'exit' to quit): ");
        fgets(buffer, BUFFER_SIZE, stdin);

        // Write the input to the named pipe
        write(fd, buffer, strlen(buffer) + 1);

        // Check for the exit condition
        if (strncmp(buffer, "exit", 4) == 0) {
            printf("Sender: Terminating connection.\n");
            break;
        }
    }

    // Close the pipe
    close(fd);
    return 0;
}
