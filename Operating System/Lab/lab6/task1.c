#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

#define FIFO_NAME "/tmp/myfifo"

int main() {
    int pid;
    int fd;
    
    // Modification 1 & 3: Change buffer size to 50 and set message to "Hello Child"
    char message[50] = "Hello Child"; 

    // Create the FIFO (named pipe)
    mkfifo(FIFO_NAME, 0666);

    pid = fork();

    if (pid < 0) {
        printf("Fork Failed\n");
        return 1;
    } else if (pid == 0) {
        // --- Child Process ---
        fd = open(FIFO_NAME, O_RDONLY);
        read(fd, message, sizeof(message));
        
        // Modification 2: Print the message two times
        printf("Child received (1st time): %s\n", message);
        printf("Child received (2nd time): %s\n", message);
        
        // Modification 4: Print the total number of characters in the message
        // We use %lu because strlen returns a size_t type.
        printf("Total characters in message: %lu\n", strlen(message));
        
        close(fd);
    } else {
        // --- Parent Process ---
        fd = open(FIFO_NAME, O_WRONLY);
        
        // Parent sends the message without taking input from the user
        write(fd, message, strlen(message) + 1);
        close(fd);
        
        printf("Parent sent the message\n");
    }

    return 0;
}

