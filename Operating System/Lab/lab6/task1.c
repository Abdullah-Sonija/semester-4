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
    
    char message[50] = "Hello Child"; 

    mkfifo(FIFO_NAME, 0666);

    pid = fork();

    if (pid < 0) {
        printf("Fork Failed\n");
        return 1;
    } else if (pid == 0) {
        
        fd = open(FIFO_NAME, O_RDONLY);
        read(fd, message, sizeof(message));
        
        printf("Child received (1st time): %s\n", message);
        printf("Child received (2nd time): %s\n", message);
        
        printf("Total characters in message: %lu\n", strlen(message));
        
        close(fd);
    } else {
        fd = open(FIFO_NAME, O_WRONLY);
        
        write(fd, message, strlen(message) + 1);
        close(fd);
        
        printf("Parent sent the message\n");
    }

    return 0;
}

