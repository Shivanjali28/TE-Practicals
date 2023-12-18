#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

sem_t rwlock;
pthread_mutex_t mutex;
int readcount; // Keep track of the number of readers reading data
int data;

// Function prototypes
void *reader_thread(void *no);
void *writer_thread(void *no);

int main() {
    int res, read, write;
    int *arg;
    printf("------------------READER-WRITER PROBLEM (Reader Priority)----------------------\n");
    printf("Enter the number of readers: ");
    scanf("%d", &read);
    printf("Enter the number of writers: ");
    scanf("%d", &write);

    // Creation of threads
    pthread_t reader, writer;

    res = sem_init(&rwlock, 0, 1);
    if (res != 0) {
        perror("Semaphore initialization failed!!");
        exit(EXIT_FAILURE);
    }

    res = pthread_mutex_init(&mutex, NULL);
    if (res != 0) {
        perror("Mutex initialization failed!!");
        exit(EXIT_FAILURE);
    }

    readcount = 0; // Initialize readcount

    // Creating reader threads
    printf("Creating reader threads:\n");
    for (int i = 0; i < read; i++) {
        printf("Creating Reader number [%d]\n", i + 1);
        arg = (int *)malloc(sizeof(int));
        *arg = i + 1;
        res = pthread_create(&reader, NULL, reader_thread, arg);
        if (res != 0) {
            perror("Thread creation failed!!");
            exit(EXIT_FAILURE);
        }
    }

    // Creating writer threads
    printf("Creating writer threads:\n");
    for (int i = 0; i < write; i++) {
        printf("Creating Writer number [%d]\n", i + 1);
        arg = (int *)malloc(sizeof(int));
        *arg = i + 1;
        res = pthread_create(&writer, NULL, writer_thread, arg);
        if (res != 0) {
            perror("Thread creation failed!!");
            exit(EXIT_FAILURE);
        }
    }

    // Wait for threads to finish
    res = pthread_join(reader, NULL);
    if (res != 0) {
        perror("Thread waiting failed");
        exit(EXIT_FAILURE);
    }
    res = pthread_join(writer, NULL);
    if (res != 0) {
        perror("Thread waiting failed");
        exit(EXIT_FAILURE);
    }

    // Destroy the semaphore and mutex
    sem_destroy(&rwlock);
    pthread_mutex_destroy(&mutex);

    return 0;
}

// Function for reader thread
void *reader_thread(void *no) {
    int *num = (int *)no;
    while (1) {
        int temp = rand() % 2 + 1;
        sleep(temp);

        pthread_mutex_lock(&mutex);
        readcount++;
        if (readcount == 1) {
            sem_wait(&rwlock);
        }
        pthread_mutex_unlock(&mutex);

        printf("R%d: Entered in READER\n", *num);
        // Read the data
        sleep(temp);
        int temp_data = data;
        printf("R%d: DATA => %d\n", *num, temp_data);
        printf("R%d: Exited from READER\n", *num);

        pthread_mutex_lock(&mutex);
        readcount--;
        if (readcount == 0) {
            sem_post(&rwlock);
        }
        pthread_mutex_unlock(&mutex);
    }
}

// Function for writer thread
void *writer_thread(void *no) {
    int *num = (int *)no;
    while (1) {
        int temp = rand() % 7;
        if (temp == 0) {
            temp = 2;
        }
        sleep(temp);

        sem_wait(&rwlock);

        pthread_mutex_lock(&mutex);
        printf("\n\t\t\t\t\tW%d: Entered in writer section\n", *num);
        data = temp * 12;
        printf("\n\t\t\t\t\tW%d: The data was changed, data=%d\n", *num, data);
        printf("\n \t\t\t\t\t\tW%d : Exited from WRITER ", *num);
        
        pthread_mutex_unlock(&mutex);
        sem_post(&rwlock);
    }
}