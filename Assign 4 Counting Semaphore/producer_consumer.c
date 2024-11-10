#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define BUFFER_SIZE 100

// Function to create a pipe
int create_pipe(int pfd[2]) {
    if (pipe(pfd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    return 0;
}

// Function to handle child process operations
void handle_child(int pfd[2]) {
    char buffer[BUFFER_SIZE];
    close(pfd[1]); // Close unused write end

    // Read from the pipe
    read(pfd[0], buffer, sizeof(buffer));  //read end (pfd[0]) and stores it in buffer
    printf("Child received: %s\n", buffer);
    close(pfd[0]); // Close read end
    _exit(0); // Exit child process
}

// Function to handle parent process operations
void handle_parent(int pfd[2]) {
    const char* message = "Hello from the parent process!";
    close(pfd[0]); // Close unused read end

    // Write to the pipe
    write(pfd[1], message, strlen(message) + 1); // Include null terminator
    close(pfd[1]); // Close write end

    // Wait for the child to finish
    wait(NULL);
}

int main() {
    int pfd[2]; // Pipe file descriptors
    pid_t cpid;

    // Create a pipe
    create_pipe(pfd);

    // Fork a child process
    cpid = fork();
    if (cpid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (cpid == 0) { // Child process
        handle_child(pfd);
    } else { // Parent process
        handle_parent(pfd);
    }

    return 0;
}

// gcc producer_consumer.c -lpthread
// ./a.out

//oe gcc -o producer_consumer producer_consumer.c -lpthread
//./producer_consumer


    
