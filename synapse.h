#ifndef SYNAPSE_H_
#define SYNAPSE_H_

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef S_CALLOC
#define S_CALLOC calloc
#endif // S_CALLOC

#ifndef S_ASSERT
#include <assert.h>
#define S_ASSERT assert
#endif // S_ASSERT

typedef struct
{
    size_t rows;
    size_t cols;
    float *es;
} Mat;

#define MAT_AT(m, i, j) (m).es[(i) * (m).cols + (j)]

float rand_float(void);

Mat mat_alloc(size_t rows, size_t cols);
void mat_dot(Mat dist, Mat a, Mat b);
void mat_sum(Mat dist, Mat a);
void mat_print(Mat m, const char *name);
#define MAT_PRINT(m) mat_print(m, #m)
void mat_rand(Mat m, float low, float high);
void mat_fill(Mat m, float x);

#endif // SYNAPSE_H_

#ifdef SYNAPSE_IMPLEMENTATION

float rand_float()
{
    return (float)rand() / (float)RAND_MAX;
}

Mat mat_alloc(size_t rows, size_t cols)
{
    Mat m;
    m.rows = rows;
    m.cols = cols;
    m.es = S_CALLOC(rows * cols, sizeof(*m.es));
    S_ASSERT(m.es != NULL);
    return m;
}

void mat_dot(Mat dist, Mat a, Mat b)
{
    S_ASSERT(a.cols == b.rows);
    S_ASSERT(dist.rows == a.rows);
    S_ASSERT(dist.cols == b.cols);

    for (size_t i = 0; i < dist.rows; i++)
    {
        for (size_t j = 0; j < dist.cols; j++)
        {
            MAT_AT(dist, i, j) = 0;
            for (size_t k = 0; k < a.cols; k++)
            {
                MAT_AT(dist, i, j) += MAT_AT(a, i, k) * MAT_AT(b, k, j);
            }
        }
    }
}

void mat_sum(Mat dist, Mat a)
{
    S_ASSERT(dist.rows == a.rows);
    S_ASSERT(dist.cols == a.cols);
    for (size_t i = 0; i < dist.rows; i++)
    {
        for (size_t j = 0; j < dist.cols; j++)
        {
            MAT_AT(dist, i, j) += MAT_AT(a, i, j);
        }
    }
}

void mat_print(Mat m, const char *name)
{
    printf("%s = [\n", name);
    for (size_t i = 0; i < m.rows; i++)
    {
        for (size_t j = 0; j < m.cols; j++)
        {
            printf("   %f ", MAT_AT(m, i, j));
        }
        printf("\n");
    }
    printf("]\n");
}

void mat_fill(Mat m, float x)
{
    for (size_t i = 0; i < m.rows; i++)
    {
        for (size_t j = 0; j < m.cols; j++)
        {
            MAT_AT(m, i, j) = x;
        }
    }
}

void mat_rand(Mat m, float low, float high)
{
    for (size_t i = 0; i < m.rows; i++)
    {
        for (size_t j = 0; j < m.cols; j++)
        {
            MAT_AT(m, i, j) = rand_float() * (high - low) + low;
        }
    }
}

#endif // SYNAPSE_IMPLEMENTATION
