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
    char *str = (char *)shmat(shmid, (void *)0, 0);

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
    shmdt(str);  
    return 0;
}
