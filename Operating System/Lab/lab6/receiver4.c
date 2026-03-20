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

    // Open the FIFO for reading
    fd = open(FIFO_NAME, O_RDONLY);
    if (fd == -1) {
        perror("Failed to open FIFO");
        return 1;
    }

    while (1) {
        // Read the message from the FIFO
        read(fd, buffer, BUFFER_SIZE);

        // Check for the exit condition
        if (strncmp(buffer, "exit", 4) == 0) {
            printf("Receiver: Exit command received. Terminating.\n");
            break;
        }

        // Print the received message
        printf("Receiver: Received message: %s", buffer);
    }

    // Close the pipe
    close(fd);
    
    // Clean up: Remove the FIFO from the file system
    unlink(FIFO_NAME);

    return 0;
}
