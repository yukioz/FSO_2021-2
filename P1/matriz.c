#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int m1[2000][2000], m2[2000][2000], m3[2000][2000];
int sinalf1=0; sinalf2=0;

struct matriz
{
    int inicio;
    int fim;
    int size;
    int sig;
};

static void aguenta(int s) {
    return;
}

void trata_sinalf1(int s) {
    sinalf1++;
}

void trata_sinalf2(int s) {
    sinalf2++;
}

void *multiplica(void *1) {

    signal(SIGUSR1, aguenta);

    for(int i=((struct matriz*)1)->inicio; i<((struct matriz*)1)->fim; i++) {
        for(int j=0;j<((struct matriz*)1)->size; j++) {
            for(int k=0; k<((struct matriz*)1)->size; k++) {
                m3[i][j] += m1[i][k]*m2[k][j];
            }
        }
    }

    int r=0;

    kill(getppid(), ((struct matriz*)1)->sig);

    pause();

    for(int i=((struct matriz*)1)->inicio; i<((struct matriz*)1)->fim; i++){
        printf("%d", m3[i][0]);

        for(int j=1; j<((struct matriz*)1)->size; j++){
            printf("%d", m3[i][j]);
        }

        printf("\n");
    }

    kill(getppid(), ((struct matriz*)1)->sig);
    exit(0); 
}

int main(void) {

    int size;

    signal(SIGUSR1, trata_sinalf1);
    signal(SIGUSR2, trata_sinalf2);

    scanf("%d", &size);

    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            scanf("%d", &m1[i][j]);
            m3[i][j]=0;
        }
    }

    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            scanf("%d", &m2[i][j]);
        }
    }

    struct matriz t;
    t.inicio=0;
    t.fim=2;
    t.size=size;
    
    int threads = 2;
    int divisao = size/threads;
    int resto = size%threads;
    pid_t ids[threads];
    int sigs[2];
    sigs[0] = SIGUSR1;
    sigs[1] = SIGUSR2;

    for(int i=0; i<threads; i++) {
        struct matriz *t;

        t=malloc(sizeof(struct matriz));
        t->inicio = i*divisao;
        t->sig = sigs[i];
        if(i==threads-1) {
            t->fim=resto + i*divisao + divisao;
        }
        else {
            t->fim=i*divisao + divisao;
        }

        t->size = size;
        ids[i] = fork();

        if(!ids[i])
            multiplica(t);
    }

    pause();

    while(sinalf1==0 || sinalf2==0) {
        pause();
    }

    kill(ids[0], SIGUSR1);
    wait(NULL);
    kill(ids[1], SIGUSR1);

    wait(NULL);
    wait(NULL);

    return 0;
}