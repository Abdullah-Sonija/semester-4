#include<stdio.h>
#include<stdlib.h>

#define ARRAY_SIZE 10000000

int main()
{
    float *a = (float *)malloc(ARRAY_SIZE * sizeof(float));
    float *b = (float *)malloc(ARRAY_SIZE * sizeof(float));
    float *c = (float *)malloc(ARRAY_SIZE * sizeof(float));


    if (a == NULL || b == NULL || c == NULL)
    {
        printf("Memory allocation failed\n");
    }
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        a[i] = i * 1.25;
        b[i] = i * 1.5;
        c[i] = a[i] + b[i];
    }
    printf("Serial addition:\n");
    printf("c value at 1000: %.3f\n", c[1000]);
    printf("c value at 10: %.3f\n", c[10]);

    free(a);
    free(b);
    free(c);
    return 0;
}
