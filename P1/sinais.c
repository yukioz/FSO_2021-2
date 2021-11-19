#include <stdio.h>
#include <signal.h>

void trata_sinal(int sig) {
    printf("recebi o sinal SIGINT\n");
}

int main(void) {
    
    signal(SIGINT, trata_sinal);

    while(1)
        pause();
}