#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

int alarmcnt = 0;

void tratarSinal(int sinal) {

    if(sinal==SIGUSR1) {
        printf("SIGUSR1 eh para aproveitar mais um pouco\n");
    }
    else if(sinal==SIGALRM) {
        alarmcnt++;
        if(alarmcnt >= 3) {
            printf("Os incomodados que se mudem, tchau\n");
            exit(0);
        }
        else {
            printf("Ai que sono, quero dormir mais um pouco\n");
        }
    }

}

int main(void) {

    signal(SIGUSR1, tratarSinal);
    signal(SIGALRM, tratarSinal);

    while(1) {

        pause();
    }

}