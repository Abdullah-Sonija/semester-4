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

    if (pipe(fd) == -1) {
        fprintf(stderr, "Pipe failed\n");
        return 1;
    }

    pid = fork();
    if (pid < 0) {
        fprintf(stderr, "Fork Failed\n");
        return 1;
    }
    if (pid > 0) { 
        close(fd[READ_END]); 

        printf("Enter sentence: ");
        fgets(sentence, BUFFER_SIZE, stdin);
        
        sentence[strcspn(sentence, "\n")] = 0;
        write(fd[WRITE_END], sentence, strlen(sentence) + 1);
        close(fd[WRITE_END]); 
        wait(NULL); 
    } 
    else { 
        close(fd[WRITE_END]); 

        read(fd[READ_END], read_msg, BUFFER_SIZE);
        
        int word_count = 0;
        int in_word = 0;
        
        for (int i = 0; read_msg[i] != '\0'; i++) {
            if (read_msg[i] == ' ' || read_msg[i] == '\t' || read_msg[i] == '\n') {
                in_word = 0;
            } else if (in_word == 0) {
                in_word = 1;
                word_count++;
            }
        }
        printf("Total words: %d\n", word_count);
        close(fd[READ_END]); 
    }
    return 0;
}
