#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int exitDoFilho = 0;

void trata(int sinal) {

    exitDoFilho = sinal;
}

int main(void) {

    signal(SIGUSR1, trata);
    signal(SIGUSR2, trata);

    pause();
    if(fork() == 0) {
        exit(0);
    }

    pause();
    wait(NULL);

    pause();
    exit(0);

}
