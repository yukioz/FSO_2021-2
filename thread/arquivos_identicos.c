#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Pode fazer uma função recursiva de comparação

//A comparação é uma "combinação"

void compara(char **argumentos){

    size_t resultadoA;
    //Armazena os nomes dos arquivos
    char **next, **atual;

    //Ponteiro para o arquivo "base" de comparação
    atual = argumentos;
    //Ponteiro para os arquivos a seguir
    next = argumentos;
    next++;

    //Abre o arquivo em modo leitura
    FILE *arqA;
    arqA = fopen(*atual, "r");
    fseek(arqA, 0L, SEEK_END);
    //Calcula o tamanho
    long szA;
    szA = ftell(arqA);
    //Retorna o ponteiro para o inicio do arquivo 
    rewind(arqA);

    //irá conter o conteúdo inteiro do arquivo a comparar ("base")
    char *bufferA;
    bufferA = (char *) malloc(sizeof(char)*szA);
    if(bufferA == NULL) {return;}
    //Copia o arquivo para o bufferA
    resultadoA = fread(bufferA, 1, szA, arqA);
    if(resultadoA != szA) {return;}

    //Para todos os arquivos depois do arquivo a comparar ("base")
    while(*next != NULL){
        
        //Abre o ponteiro para o próximo arquivo em modo leitura
        FILE *arqN;
        arqN = fopen(*next, "r");
        //Calcula o tamanho
        fseek(arqN, 0L, SEEK_END);
        long szN;
        szN = ftell(arqN);
        //Retorna o ponteiro para i inicio do arquivo
        rewind(arqN);

        //Compara o tamanho dos arquivos -> se diferentes, imprime: "diferentes", se iguais -> checar conteúdo
        if(szN != szA){
            printf("%s %s diferentes\n", *atual, *next);
        } else {
            //-------------Verificar o conteúdo-----------

            //Irá conter todo o conteúdo do arquivo N ("a ser comparado")
            char *bufferN;
            bufferN = (char *) malloc(sizeof(char)*szN);
            if(bufferN == NULL) {return;}
            //Copia o arquivo para o bufferN
            size_t resultadoN = fread(bufferN, 1, szN, arqN);
            if(resultadoN != szN) {return;}

            //Comparacao dos dois arquivos
            if(memcmp(bufferA, bufferN, resultadoN) == 0){
                printf("%s %s iguais\n", *atual, *next);
            } else {
                printf("%s %s diferentes\n", *atual, *next);
            }
            //Libera a memória do bufferN
            free(bufferN);
        }

        //Pega o próximo nome de arquivo e libera a memória utilizada
        next++;
        fclose(arqN);
    }

    //Libera a memória do arquivo "base" e fecha o arquivo
    free(bufferA);
    fclose(arqA);
    //pega o próximo caminho de arquivo
    atual++;
    if(*atual != NULL){
        compara(atual);
    }
    return;
}

int main (int argc, char **argv) {
    
    argv++;
    compara(argv);

    return 0;
}