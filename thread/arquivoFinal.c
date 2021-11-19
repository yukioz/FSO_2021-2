#include <stdio.h>
#include <string.h>
#include <stdlib.h>

long offset = 0;

void indetificar(char **params)
{

    char **lendo;

    lendo = params;

    FILE *arquivo;
    arquivo = fopen(*lendo, "r");

    char **prox;

    prox = &params[1];
    while (*prox != NULL)
    {
        int flag = 1;
        FILE *arquivo_prox;
        arquivo_prox = fopen(*prox, "r");
        
        while(1) {
            char ch1, ch2;
            ch1 = fgetc(arquivo);
            ch2 = fgetc(arquivo_prox);

            if(ch1 != ch2) {
                printf("%s %s diferentes\n", *lendo, *prox);
                flag = 0;
                break;
            }

            if(feof(arquivo) || feof(arquivo_prox)) {
                break;
            }
        }

        if(flag) {
            printf("%s %s iguais\n", *lendo, *prox);
        }

        fclose(arquivo_prox);
        rewind(arquivo);

        prox++;
    }

    fclose(arquivo);

    lendo++;
    if (*lendo != NULL)
    {
        indetificar(lendo);
    }
}

int main(int argc, char **argv)
{

    // passa posição 1 de argv não a 0.
    indetificar(&argv[1]);

    return 0;
}