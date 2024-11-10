//Server.c

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>

#define SHM_SIZE 1024  // Size of shared memory segment

int main() {
    key_t key = ftok("shmfile", 65);  // Generate unique key
    int shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);  // Create shared memory

    // Attach to shared memory
    char *str = (char *)shmat(shmid, (void *)0, 0);  //shared memo attch

    printf("Server: Listening for messages...\n");

    while (1) {
        // Check for new messages every second
        sleep(1);
        if (strlen(str) > 0) {  // If there's a message
            printf("Server: Message received: %s\n", str);
            memset(str, 0, SHM_SIZE);  // Clear the message after displaying
        }
    }

    // Detach from shared memory
    shmdt(str);  //shared memo detach
    return 0;
}
--------------------------------------------
//client.c

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define SHM_SIZE 1024  // Size of shared memory segment

int main() {
    key_t key = ftok("shmfile", 65);  // Generate unique key
    int shmid = shmget(key, SHM_SIZE, 0666);  // Access shared memory

    // Attach to shared memory
    char *str = (char *)shmat(shmid, (void *)0, 0);

    char input[SHM_SIZE];
    
    while (1) {
        printf("Client: Enter message: ");
        fgets(input, SHM_SIZE, stdin);  // Read input from user
        
        input[strcspn(input, "\n")] = 0;  // Remove newline character
        
        // Write the message to shared memory
        strcpy(str, input);
    }

    // Detach from shared memory
    shmdt(str);  
    return 0;
}

