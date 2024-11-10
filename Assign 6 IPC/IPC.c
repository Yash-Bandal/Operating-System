    
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include<sys/wait.h>

#define BUFFER_SIZE 100

int main() {
    int pipefd[2]; // Pipe file descriptors
    pid_t cpid;   //pid of child
    char buffer[BUFFER_SIZE];

    // Create a pipe..chk if not exist
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork a child process
    cpid = fork();
    if (cpid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (cpid == 0) { // Child process
        close(pipefd[1]); // Close unused write end

        // Read from the pipe
        read(pipefd[0], buffer, sizeof(buffer));
        printf("Child received: %s\n", buffer);
        close(pipefd[0]); // Close read end
        _exit(0); // Exit child process
    } else { // Parent process
        close(pipefd[0]); // Close unused read end

        // Write to the pipe
        const char* message = "Hello from the parent process!";
        write(pipefd[1], message, strlen(message) + 1); // Include null terminator
        close(pipefd[1]); // Close write end

        // Wait for the child to finish
        wait(NULL);
    }

    return 0;
}






// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <string.h>
// #include <sys/types.h>
// #include <sys/wait.h>

// #define BUFFER_SIZE 1024

// int main() {
//     int pipe1[2]; // Pipe for parent to child (writing file path)
//     int pipe2[2]; // Pipe for child to parent (writing file contents)
    
//     if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
//         perror("pipe");
//         exit(EXIT_FAILURE);
//     }

//     pid_t pid = fork();
//     if (pid == -1) {
//         perror("fork");
//         exit(EXIT_FAILURE);
//     }

//     if (pid == 0) { // Child process
//         close(pipe1[1]); // Close unused write end of pipe1
//         close(pipe2[0]); // Close unused read end of pipe2
        
//         char file_path[BUFFER_SIZE];
//         read(pipe1[0], file_path, BUFFER_SIZE); // Read file path from parent

//         // Open the file and read contents
//         FILE *file = fopen(file_path, "r");
//         if (file == NULL) {
//             perror("fopen");
//             exit(EXIT_FAILURE);
//         }

//         char buffer[BUFFER_SIZE];
//         while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
//             write(pipe2[1], buffer, strlen(buffer)); // Write file contents to parent
//         }
//         fclose(file);
//         close(pipe2[1]); // Close write end of pipe2
//         exit(EXIT_SUCCESS);
//     } else { // Parent process
//         close(pipe1[0]); // Close unused read end of pipe1
//         close(pipe2[1]); // Close unused write end of pipe2

//         // Write the file path to the child
//         const char *file_path = "example.txt"; // Change this to your file path
//         write(pipe1[1], file_path, strlen(file_path) + 1); // +1 to include null terminator

//         wait(NULL); // Wait for child process to finish

//         // Read contents sent back from child
//         char buffer[BUFFER_SIZE];
//         while (read(pipe2[0], buffer, BUFFER_SIZE) > 0) {
//             printf("%s", buffer); // Display contents on standard output
//         }

//         close(pipe1[1]); // Close write end of pipe1
//         close(pipe2[0]); // Close read end of pipe2
//     }

//     return 0;
// }

------------------------------------------------------------------------------
