#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

void fazoqueopaifaz() {
    printf("%d: Sou o pai\n", getpid());
    pid_t p;
    p = wait(NULL);
    printf("O filho %d terminou\n", p);
    exit(0);
}

void fazoqueofilhofaz() {
    printf("%d: Sou o filho\n", getpid());
    sleep(5);
    printf("%d: Eu sou o filho e meu pai é %d\n", getpid(), getppid());
    exit(0);
    printf("Aindas vivo?\n");
}

int main (void) {
    pid_t p;
    p=fork();

    if(p>0) {
        fazoqueopaifaz();
    }
    else if(p==0) {
        fazoqueofilhofaz();
    }
    printf("Olá mundo\n");
}