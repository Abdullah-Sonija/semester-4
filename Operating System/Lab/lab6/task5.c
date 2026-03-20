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
    int *ptr; // Using an int pointer since we are passing an integer
    pid_t pid;

    // Create the shared memory object
    fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    if (fd == -1) {
        perror("Shared memory failed");
        return 1;
    }

    // Configure the size of the shared memory object
    ftruncate(fd, SIZE);

    // Map the shared memory object to the process's address space
    ptr = (int *)mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED) {
        perror("Map failed");
        return 1;
    }

    // 1. Parent process asks the user to enter an integer number[cite: 227].
    int input_num;
    printf("Enter number: ");
    scanf("%d", &input_num);

    // 2. Parent writes the number into shared memory[cite: 228].
    *ptr = input_num;

    // Fork the child process
    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        // --- Child Process ---
        
        // 3. Child process reads the number from shared memory[cite: 229].
        int read_num = *ptr;
        
        // 4. Child calculates the square of the number[cite: 230].
        int square = read_num * read_num;
        
        // 5. Child prints the result on the screen[cite: 231].
        printf("Square of %d is: %d\n", read_num, square);
        
    } else {
        // --- Parent Process ---
        
        // Wait for the child process to finish its task
        wait(NULL); 
        
        // Clean up: unmap and remove the shared memory object
        munmap(ptr, SIZE);
        shm_unlink(name);
    }

    return 0;
}
