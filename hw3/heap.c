//
// Created by 陈昱聪 on 2021/3/29.
//

#include <stdio.h>

int heap[32] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int len = 0;

int input[12] = {5, 4, 3, 7, 0, 9, 1, 2, 6, 8, -1, -2};
int input_len = 12;

void swap(int a, int b)
{
    int tmp = heap[a];
    heap[a] = heap[b];
    heap[b] = tmp;
}

int insert(int elem)
{
    int i, j;
    /*
     s1, s2
     */
    if (len + 1 > 32) return -1;

    heap[len] = elem;
    len++;

    for (i = len - 1; i > 0 ; )
    {
        j = (i - 1) / 2;
        if (heap[i] < heap[j])
        {
            swap(i, j);
            i = j;
        }
        else break;
    }

    return 0;
}

int pop()
{
    int i, j;
    
    if (len - 1 < 0) return -1;
    
    swap(0, len - 1);
    len--;

    for (i = 0; (2*i + 1) < len;)
    {
        if ((2 * i + 2) < len)
        {
            if (heap[2 * i + 2] < heap[2 * i + 1])
            {
                if (heap[2 * i + 2] < heap[i])
                {
                    swap(i, 2 * i + 2);
                    i = 2 * i + 2;
                }
                else break;
            }
            else
            {
                if (heap[2 * i + 1] < heap[i])
                {
                    swap(i, 2 * i + 1);
                    i = 2 * i + 1;
                }
                else break;
            }
        }
        else
        {
            if (heap[2*i+1] < heap[i])
            {
                swap(i, 2 * i + 1);
                i = 2 * i + 1;
            }
            else break;
        }

    }

    return heap[len];
}

void print_heap()
{
    int i;
    for (i = 0; i < len; i++)
    {
        printf("%d", heap[i]);
        if (i == len - 1) {
            printf("\n");
            break;
        }
        printf(" ");
    }

}

int main()
{
    int i, tmp;
    for (i = 0; i < input_len; i++)
    {
        switch (input[i])
        {
            case -1:
                tmp = pop();
                printf("%d\n", tmp);
                break;
            case -2:
                print_heap();
                break;
            default:
                tmp = insert(input[i]);
                if (tmp == -1)
                {
                    printf("over_flow!\n");
                    return -1;
                }
                break;
        }
    }

    return 0;
}
