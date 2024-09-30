#include <iostream>
#include <thread>
#include <semaphore.h>
#include <mutex>
#include <vector>
#include <chrono>

using namespace std;

const int BUFFER_SIZE = 5; // Size of the buffer
vector<int> buffer(BUFFER_SIZE); // The shared buffer
int count = 0; // Current number of items in the buffer
mutex mtx; // Mutex for mutual exclusion
sem_t empty; // Semaphore to count empty slots
sem_t full; // Semaphore to count full slots

// Producer function
void producer(int id) {
    for (int i = 0; i < 10; ++i) {
        this_thread::sleep_for(chrono::milliseconds(rand() % 100)); // Simulate production time

        int item = rand() % 100; // Produce an item

        sem_wait(&empty); // Decrease empty count
        mtx.lock(); // Lock the buffer
        buffer[count] = item; // Add item to buffer
        cout << "Producer " << id << " produced: " << item << endl;
        count++; // Increase the count
        mtx.unlock(); // Unlock the buffer
        sem_post(&full); // Increase full count
    }
}

// Consumer function
void consumer(int id) {
    for (int i = 0; i < 10; ++i) {
        sem_wait(&full); // Decrease full count
        mtx.lock(); // Lock the buffer
        int item = buffer[count - 1]; // Consume an item
        count--; // Decrease the count
        cout << "Consumer " << id << " consumed: " << item << endl;
        mtx.unlock(); // Unlock the buffer
        sem_post(&empty); // Increase empty count
        this_thread::sleep_for(chrono::milliseconds(rand() % 100)); // Simulate consumption time
    }
}

int main() {
    // Initialize semaphores
    sem_init(&empty, 0, BUFFER_SIZE); // Start with all slots empty
    sem_init(&full, 0, 0); // Start with no items

    // Create producer and consumer threads
    thread producers[2], consumers[2];

    for (int i = 0; i < 2; ++i) {
        producers[i] = thread(producer, i + 1);
        consumers[i] = thread(consumer, i + 1);
    }

    // Join threads
    for (int i = 0; i < 2; ++i) {
        producers[i].join();
        consumers[i].join();
    }

    // Destroy semaphores
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}
//g++ -o producer_consumer producer_consumer.cpp -lpthread

//./producer_consumer

