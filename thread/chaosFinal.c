#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

int numeros[200000];
sem_t semaforo;
sem_t seeds;
int mi, bi;
int somaglobal;

void register_numbers(int s1, int s2)
{
    for (int i = 0; i < 100000; i++)
    {
        numeros[i] = rand_r(&s1);
        numeros[i + 100000] = rand_r(&s2);
    }
};

struct busca
{
    int mi;
    int bi;
};

void *Consumer1()
{
    // struct busca *x1 = (struct busca *)p;
    int cnt = 0;

    for (int i = 100000; i < 200000; i++)
    {
        if (numeros[i] % mi == bi)
        {
            cnt++;
        }
    }

    sem_wait(&semaforo);
    somaglobal+=cnt;
    sem_post(&semaforo);
}

void *Consumer2()
{
    int count = 0;

    for (int i = 0; i < 100000; i++)
    {
        if (numeros[i] % mi == bi)
        {
            count++;
        }
    }

    sem_wait(&semaforo);
    somaglobal+=count;
    sem_post(&semaforo);
}

int main(void)
{
    // pthreads
    pthread_t ptid1, ptid2;

    // Inicia semáforo
    sem_init(&semaforo, 0, 1);
    sem_init(&seeds, 0, 1);
    struct busca x;

    // sementes
    int s1, s2;

    // modulo e valor procurado
    // int mi, bi;

    // Preencher vetor de busca
    scanf("%d %d", &s1, &s2);
    register_numbers(s1, s2);

    while (scanf("%d %d", &mi, &bi) != EOF)
    {
        //x.mi=mi;
        //x.bi=bi;
        pthread_create(&ptid1, NULL, Consumer1, NULL); //(void *)&x
        pthread_create(&ptid2, NULL, Consumer2, NULL);
        pthread_join(ptid1, NULL);
        pthread_join(ptid2, NULL);

        printf("%d\n", somaglobal);
        somaglobal=0;
    }
}
