#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

void tratarSinal(int sinal) {
    int final;
    char string[11];

    final = scanf(" %s", string);

    if(final == EOF) {
        exit(0);
    }

    if(sinal == SIGUSR1 && string[3] == 'r') {
        printf("Certo\n");
    }
    else if(sinal == SIGUSR2 && string[3] == 'a') {
        printf("Certo\n");
    }
    else if(sinal == SIGINT && string[3] == '1') {
        printf("Certo\n");
    }
    else if(sinal == SIGTERM && string[3] == '2') {
        printf("Certo\n");
    }
    else if(sinal == SIGALRM && string[3] == 'e') {
        printf("Certo\n");
    }
    else {
        printf("Erro\n");
        signal(SIGALRM ,tratarSinal);
    }
}

int main(void) {

    signal(SIGUSR1 ,tratarSinal);
    signal(SIGUSR2 ,tratarSinal);
    signal(SIGINT ,tratarSinal);
    signal(SIGTERM ,tratarSinal);
    signal(SIGALRM ,tratarSinal);

    while(1) {
        
        // espera uma entrada
        pause();
    }
}