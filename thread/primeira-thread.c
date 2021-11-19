#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void *funcao(void *a) {
    printf("sou uma thread\n");

    while(1);
}

int main (void) {

    pthread_t tid;

    pthread_create(&tid, NULL, &funcao, NULL);

    printf("Thread criada\n");

    printf("Thread principal dormindo um pouco\n");
    sleep(5);
    printf("tchau\n");

    return 0;
}
