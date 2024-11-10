
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define N 5
#define THINKING 2
#define HUNGRY 1
#define EATING 0
#define LEFT (phnum + 4) % N
#define RIGHT (phnum + 1) % N

int state[N];
int phil[N] = { 0, 1, 2, 3, 4 };

pthread_mutex_t mutex;
pthread_cond_t S[N];

void test(int phnum) {
    if (state[phnum] == HUNGRY && 
        state[LEFT] != EATING && 
        state[RIGHT] != EATING) {
        
        // Change state to EATING
        state[phnum] = EATING;

        printf("Philosopher %d takes fork %d and %d\n", phnum + 1, LEFT + 1, phnum + 1);
        printf("Philosopher %d is Eating\n", phnum + 1);

        // Notify the philosopher that they can start eating
        pthread_cond_signal(&S[phnum]);
    }
}

void take_fork(int phnum) {
    pthread_mutex_lock(&mutex);

    // Change state to HUNGRY
    state[phnum] = HUNGRY;
    printf("Philosopher %d is Hungry\n", phnum + 1);

    // Eat if neighbors are not eating
    test(phnum);

    // If unable to eat, wait to be signaled
    while (state[phnum] != EATING) {
        pthread_cond_wait(&S[phnum], &mutex);
    }

    pthread_mutex_unlock(&mutex);
    sleep(1); // Simulate eating time
}

void put_fork(int phnum) {
    pthread_mutex_lock(&mutex);

    // Change state to THINKING
    state[phnum] = THINKING;
    printf("Philosopher %d putting fork %d and %d down\n", phnum + 1, LEFT + 1, phnum + 1);
    printf("Philosopher %d is Thinking\n", phnum + 1);

    // Test neighboring philosophers
    test(LEFT);
    test(RIGHT);

    pthread_mutex_unlock(&mutex);
}

void* philosopher(void* num) {
    int* phnum = (int*)num;

    while (1) {
        take_fork(*phnum);  //* not & silly
        put_fork(*phnum);
    }

    return NULL; // To satisfy the return type of the function
}

int main() {

    //1 Initialize
    pthread_t threads[N];
    pthread_mutex_init(&mutex, NULL);

    //2 Create
    for (int i = 0; i < N; i++) {
        state[i] = THINKING; // Initialize state to THINKING
        pthread_cond_init(&S[i], NULL);
        int* arg = malloc(sizeof(*arg)); // Allocate memory for argument
        *arg = i; // Assign philosopher number
        pthread_create(&threads[i], NULL, philosopher, arg);
        printf("Philosopher %d is thinking\n", i + 1);
    }
    
   //3 Join
    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }

    //4 Destroy
    pthread_mutex_destroy(&mutex);
    for (int i = 0; i < N; i++) {
        pthread_cond_destroy(&S[i]);
    }

    return 0;
}

//gcc -o dining_philosophers dining_philosophers.c -pthread
//./dining_philosophers
