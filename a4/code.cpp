#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
using namespace std;

#define NUM_READERS 2
#define NUM_WRITERS 2

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_reader = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_writer = PTHREAD_COND_INITIALIZER;

int readers_count = 0;
int writers_count = 0;
int resource = 0;
bool syncr = true;

void *reader(void *arg) {
    int reader_id = *((int *) arg);
    if (syncr) {
        pthread_mutex_lock(&mutex);
        while(writers_count > 0) {
            cout << "Reader " << reader_id << " is waiting" << endl;
            pthread_cond_wait(&cond_reader, &mutex);
        }
        readers_count++;
        pthread_mutex_unlock(&mutex);
        cout << "Reader " << reader_id << " reading shared resource" << endl;
        sleep(1);
        pthread_mutex_lock(&mutex);
        readers_count--;
        if (readers_count == 0) {
            pthread_cond_signal(&cond_writer);
        }
        pthread_mutex_unlock(&mutex);
    }
    else {
        cout << "Reader " << reader_id << " reading shared resource" << endl;
        sleep(1);
    }
    cout << "Reader " << reader_id << " completed with reading, CS is free." << endl;
    return NULL;
}

void *writer(void *arg) {
    int writer_id = *((int *) arg);
    if (syncr) {
        pthread_mutex_lock(&mutex);
        writers_count++;
        while(readers_count > 0 || writers_count > 1) {
            cout << "Writer " << writer_id << " is not allowed" << endl;
            pthread_cond_wait(&cond_writer, &mutex);
        }
        pthread_mutex_unlock(&mutex);
        cout << "Writer " << writer_id << " writing shared resource" << endl;
        sleep(1);
        pthread_mutex_lock(&mutex);
        writers_count--;
        pthread_cond_signal(&cond_writer);
        pthread_cond_broadcast(&cond_reader);
        pthread_mutex_unlock(&mutex);
    }
    else {
        cout << "Writer " << writer_id << " writing shared resource" << endl;
        sleep(1);
    }
    cout << "Writer " << writer_id << " completed with writing, CS is free." << endl;
    return NULL;
}

int main() {
    pthread_t readers[NUM_READERS];
    pthread_t writers[NUM_WRITERS];
    int reader_ids[NUM_READERS];
    int writer_ids[NUM_WRITERS];
    for (int i=0; i<NUM_READERS; i++) {
        reader_ids[i] = i+1;
        writer_ids[i] = i+1;
    }
    srand(time(NULL));
    cout << "------------------------------------------" << endl;
    cout << "With sync" << endl;

    syncr = true;
    cout << "R-R case" << endl;
    pthread_create(&readers[0], NULL, reader, &reader_ids[0]);
    pthread_create(&readers[1], NULL, reader, &reader_ids[1]);
    pthread_join(readers[0], NULL);
    pthread_join(readers[1], NULL);

    syncr = true;
    cout << "R-W case" << endl;
    pthread_create(&readers[0], NULL, reader, &reader_ids[0]);
    pthread_create(&writers[0], NULL, writer, &writer_ids[0]);
    pthread_join(readers[0], NULL);
    pthread_join(writers[0], NULL);

    syncr = true;
    cout << "W-R case" << endl;
    pthread_create(&writers[0], NULL, writer, &writer_ids[0]);
    pthread_create(&readers[0], NULL, reader, &reader_ids[0]);
    pthread_join(writers[0], NULL);
    pthread_join(readers[0], NULL);

    syncr = true;
    cout << "W-W case" << endl;
    pthread_create(&writers[0], NULL, writer, &writer_ids[0]);
    pthread_create(&writers[1], NULL, writer, &writer_ids[1]);
    pthread_join(writers[0], NULL);
    pthread_join(writers[1], NULL);

    cout << "------------------------------------------" << endl;
    cout << "Without sync" << endl;

    syncr = false;
    cout << "R-R case" << endl;
    pthread_create(&readers[0], NULL, reader, &reader_ids[0]);
    pthread_create(&readers[1], NULL, reader, &reader_ids[1]);
    pthread_join(readers[0], NULL);
    pthread_join(readers[1], NULL);

    syncr = false;
    cout << "R-W case" << endl;
    pthread_create(&readers[0], NULL, reader, &reader_ids[0]);
    pthread_create(&writers[0], NULL, writer, &writer_ids[0]);
    pthread_join(readers[0], NULL);
    pthread_join(writers[0], NULL);

    syncr = false;
    cout << "W-R case" << endl;
    pthread_create(&writers[0], NULL, writer, &writer_ids[0]);
    pthread_create(&readers[0], NULL, reader, &reader_ids[0]);
    pthread_join(writers[0], NULL);
    pthread_join(readers[0], NULL);

    syncr = false;
    cout << "W-W case" << endl;
    pthread_create(&writers[0], NULL, writer, &writer_ids[0]);
    pthread_create(&writers[1], NULL, writer, &writer_ids[1]);
    pthread_join(writers[0], NULL);
    pthread_join(writers[1], NULL);

    return 0;
}
