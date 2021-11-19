#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max;
int intArray[100001];
int front = 0;
int rear = -1;
int itemCount = 0;

int isFull()
{
    if (itemCount == max)
        return 1;

    return 0;
}

void insert(int data)
{
    // printf(">> v[%d] = %d\n", rear + 1, data);
    if (rear == max - 1)
    {
        rear = -1;
    }

    intArray[++rear] = data;

    if(!isFull())
        itemCount++;
}

int check_array(int num)
{

    for (int i = 0; i < itemCount; i++)
    {
        if (intArray[i] == num)
        {
            return 0;
        }
    }

    insert(num);
    return 1;
}

int main(void)
{

    int vetor[100000];
    int num;
    // int Q;
    int N;
    int page_fault = 0;
    int p1 = 0, p2 = 0;
    int bool = 0;

    scanf("%d", &N);

    for (int i = 0; i < N; i++)
    {
        scanf("%d", &num);
        vetor[i] = num;
    }

    while (scanf("%d", &max) != EOF)
    {
        printf("%d ", max);
        for (int i = 0; i < N; i++)
        {
            page_fault += check_array(vetor[i]);
        }
        printf("%d\n", page_fault);

        if (p1 != 0 && p2 != 0)
        {
            if (max > p1 && page_fault > p2)
            {
                bool = 1;
            }
            else
            {
                p1 = max;
                p2 = page_fault;
            }
        }
        else
        {
            p1 = max;
            p2 = page_fault;
        }

        front = 0;
        rear = -1;
        itemCount = 0;
        page_fault = 0;
    }

    if (bool == 1)
    {
        printf("Belady detectado\n");
    }
    else
    {
        printf("Sem anomalia\n");
    }
}