#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define FIFO_NAME "/tmp/myfifo"

int main() {
    int fd;
    int number;

    // Create the FIFO (named pipe) if it doesn't exist
    // 0666 grants read and write permissions
    mkfifo(FIFO_NAME, 0666);

    // 1. Ask the user to enter an integer number
    printf("Enter number: ");
    scanf("%d", &number);

    // Open the FIFO for writing only. 
    // Note: This will block until the consumer opens it for reading.
    fd = open(FIFO_NAME, O_WRONLY);
    if (fd == -1) {
        perror("Failed to open FIFO");
        return 1;
    }

    // 2. Write the number to the FIFO
    write(fd, &number, sizeof(number));
    
    // Close the pipe
    close(fd);

    return 0;
}
