#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define FIFO_NAME "/tmp/myfifo"

int main() {
    int fd;
    int number;

    // Open the FIFO for reading only
    fd = open(FIFO_NAME, O_RDONLY);
    if (fd == -1) {
        perror("Failed to open FIFO");
        return 1;
    }

    // 1. Read the number from FIFO
    read(fd, &number, sizeof(number));

    // 2. Check whether the number is even or odd
    // 3. Display the result
    if (number % 2 == 0) {
        printf("%d is an Even number\n", number);
    } else {
        printf("%d is an Odd number\n", number);
    }

    // Close the pipe
    close(fd);
    
    // Clean up: Remove the FIFO from the file system
    unlink(FIFO_NAME);

    return 0;
}
