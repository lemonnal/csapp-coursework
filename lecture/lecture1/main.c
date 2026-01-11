#include <stdio.h>
#include <time.h>
typedef struct
{
    int a[2];
    double d;
} struct_t;

double fun(int i)
{
    volatile struct_t s;
    s.d = 3.14;
    s.a[i] = 1073741824; /* Possibly out of bounds */
    return s.d;
}

void copyij1(int src[2048][2048], int dst[2048][2048])
{
    int i, j;
    for (i = 0; i < 2048; i++)
        for (j = 0; j < 2048; j++)
            dst[i][j] = src[i][j];
}

void copyij2(int src[2048][2048], int dst[2048][2048])
{
    int i, j;
    for (j = 0; j < 2048; j++)
        for (i = 0; i < 2048; i++)
            dst[i][j] = src[i][j];
}

int src1[2048][2048];
int dst1[2048][2048];
clock_t start1, end1;

int src2[2048][2048];
int dst2[2048][2048];
clock_t start2, end2;

int main()
{
#if 0                           // Question 1
    printf("%.12lf\n", fun(0)); // 3.140000000000
    printf("%.12lf\n", fun(1)); // 3.140000000000
    printf("%.12lf\n", fun(2)); // 3.139999866486
    printf("%.12lf\n", fun(3)); // 2.000000610352
    printf("%.12lf\n", fun(4)); // 3.140000000000
    printf("%.12lf\n", fun(5)); // 3.140000000000
    printf("%.12lf\n", fun(6)); // *** stack smashing detected ***: terminated
#elif 1                         // Question 2
    start1 = clock();
    copyij1(src1, dst1);
    end1 = clock();
    printf("copyij1: %f\n", (double)(end1 - start1) / CLOCKS_PER_SEC);

    start2 = clock();
    copyij2(src2, dst2);
    end2 = clock();
    printf("copyij2: %f\n", (double)(end2 - start2) / CLOCKS_PER_SEC);
#endif
    return 0;
}