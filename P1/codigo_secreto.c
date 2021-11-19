#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

// variável global
int senha = 0;

void trata(int num) {
    printf("Recebi %d\n", num);
    if(senha==0 && num == SIGINT) {
        senha++;
    }
    else if(senha==1 && num==SIGUSR2) {
        senha++;
    }
    else if(senha==2 && num==SIGTERM) {
        senha++;
        printf("Senha acionada\n");
    }
    else if(num==SIGINT) {
        senha=1;
    }
    else if(senha==3 && num==SIGUSR1) {
        printf("Tchau\n");
        exit(0);
    }
    else {
        senha = 0;
    }
}

int main(void) {

    signal(SIGINT, trata);
    signal(SIGTERM, trata);
    signal(SIGUSR1, trata);
    signal(SIGUSR2, trata);

    // loop infinito
    while(1){
        pause();
    }
}