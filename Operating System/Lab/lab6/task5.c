#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/wait.h>

int main() {
    const int SIZE = 4096;
    const char *name = "OS_SHM_TASK5";
    int fd;
    int *ptr;
    pid_t pid;

    fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    if (fd == -1) {
        perror("Shared memory failed");
        return 1;
    }

    ftruncate(fd, SIZE);

    ptr = (int *)mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED) {
        perror("Map failed");
        return 1;
    }

    int input_num;
    printf("Enter number: ");
    scanf("%d", &input_num);

    *ptr = input_num;

    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        int read_num = *ptr;
        int square = read_num * read_num;
        printf("Square of %d is: %d\n", read_num, square);
    } 
    else {
        wait(NULL); 
        munmap(ptr, SIZE);
        shm_unlink(name);
    }
    return 0;
}
