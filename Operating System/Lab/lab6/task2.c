#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define BUFFER_SIZE 100
#define READ_END 0
#define WRITE_END 1

int main() {
    char sentence[BUFFER_SIZE];
    char read_msg[BUFFER_SIZE];
    int fd[2];
    pid_t pid;

    // Create the ordinary pipe
    if (pipe(fd) == -1) {
        fprintf(stderr, "Pipe failed\n");
        return 1;
    }

    // Fork a child process
    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork Failed\n");
        return 1;
    }

    if (pid > 0) { 
        // --- Parent Process ---
        close(fd[READ_END]); // Close unused read end

        // 1. Parent asks user to enter a sentence
        printf("Enter sentence: ");
        fgets(sentence, BUFFER_SIZE, stdin);
        
        // Strip the newline character left by fgets for cleaner processing
        sentence[strcspn(sentence, "\n")] = 0;

        // 2. Parent sends the sentence to the child through the pipe
        write(fd[WRITE_END], sentence, strlen(sentence) + 1);
        close(fd[WRITE_END]); // Close write end when done
        
        wait(NULL); // Wait for child to complete before exiting
        
    } else { 
        // --- Child Process ---
        close(fd[WRITE_END]); // Close unused write end

        // Read the sentence from the pipe
        read(fd[READ_END], read_msg, BUFFER_SIZE);
        
        // 3. Child process counts the number of words
        int word_count = 0;
        int in_word = 0;
        
        for (int i = 0; read_msg[i] != '\0'; i++) {
            // Check for spaces, tabs, or newlines to identify word boundaries
            if (read_msg[i] == ' ' || read_msg[i] == '\t' || read_msg[i] == '\n') {
                in_word = 0;
            } else if (in_word == 0) {
                in_word = 1;
                word_count++;
            }
        }

        // 4. Child prints the total word count
        printf("Total words: %d\n", word_count);
        
        close(fd[READ_END]); // Close read end when done
    }

    return 0;
}
