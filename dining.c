#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5

sem_t forks[N];
pthread_mutex_t mutex;

void* philosopher(void* num)
{
    int id = *(int*)num;

    while (1)
    {
        printf("Philosopher %d is thinking\n", id);
        sleep(1);


        pthread_mutex_lock(&mutex);

        sem_wait(&forks[id]);
        sem_wait(&forks[(id + 1) % N]);

        pthread_mutex_unlock(&mutex);


        printf("Philosopher %d is eating\n", id);
        sleep(1);


        sem_post(&forks[id]);
        sem_post(&forks[(id + 1) % N]);

        printf("Philosopher %d finished eating\n", id);
    }
}

int main()
{
    pthread_t ph[N];
    int id[N];

    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < N; i++)
        sem_init(&forks[i], 0, 1);

    for (int i = 0; i < N; i++)
    {
        id[i] = i;
        pthread_create(&ph[i], NULL, philosopher, &id[i]);
    }

    for (int i = 0; i < N; i++)
        pthread_join(ph[i], NULL);

    return 0;
}
