#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "../include/rbtree.h"
#include "../include/benchmark.h"
#include "../include/csv.h"

const size_t INPUT_SIZES[NUM_INPUT_SIZES] =
{
    1,
    5,
    10,
    25,
    50,
    100,
    250,
    1000,
    2500,
    5000,
    7500,
    10000,
    25000,
    50000,
    75000,
    100000,
    250000,
    500000,
    750000,
    1000000,
    2500000,
    5000000,
    10000000,
    25000000,
    50000000,
    100000000
};


static double get_time_seconds(void)
{
    struct timespec ts;

    clock_gettime(
        CLOCK_MONOTONIC,
        &ts);

    return
        (double)ts.tv_sec +
        ((double)ts.tv_nsec / 1000000000.0);
}


double benchmark_mean(
    const double *values,
    int count)
{
    double sum = 0.0;

    for (int i = 0; i < count; i++)
    {
        sum += values[i];
    }

    return sum / count;
}

double benchmark_stddev(
    const double *values,
    int count,
    double mean)
{
    double sum = 0.0;

    for (int i = 0; i < count; i++)
    {
        double diff = values[i] - mean;

        sum += diff * diff;
    }

    return sqrt(sum / count);
}

double benchmark_min(
    const double *values,
    int count)
{
    double min = values[0];

    for (int i = 1; i < count; i++)
    {
        if (values[i] < min)
        {
            min = values[i];
        }
    }

    return min;
}

double benchmark_max(
    const double *values,
    int count)
{
    double max = values[0];

    for (int i = 1; i < count; i++)
    {
        if (values[i] > max)
        {
            max = values[i];
        }
    }

    return max;
}

BenchmarkStats benchmark_calculate(
    const double *values,
    int count)
{
    BenchmarkStats stats;

    stats.mean =
        benchmark_mean(values, count);

    stats.stddev =
        benchmark_stddev(
            values,
            count,
            stats.mean);

    stats.min =
        benchmark_min(values, count);

    stats.max =
        benchmark_max(values, count);

    return stats;
}


static unsigned int seed = 123456789;

static inline unsigned int fast_rand(void)
{
    seed = seed * 1103515245u + 12345u;
    return seed;
}

static int *generate_random_array(size_t size)
{
    int *array =
        (int *)malloc(size * sizeof(int));

    if (array == NULL)
    {
        fprintf(stderr,
                "Error allocating memory.\n");

        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < size; i++)
    {
        array[i] = (fast_rand() % 100000) + 1;
    }

    return array;
}

static double benchmark_insert(
    const int *values,
    size_t size)
{
    RBTree *tree =
        rbtree_create();

    double start =
        get_time_seconds();

    for (size_t i = 0; i < size; i++)
    {
        rbtree_insert(
            tree,
            values[i]);
    }

    double end =
        get_time_seconds();

    rbtree_destroy(tree);

    return end - start;
}

static double benchmark_search(
    const int *values,
    size_t size)
{
    RBTree *tree =
        rbtree_create();

    for (size_t i = 0; i < size; i++)
    {
        rbtree_insert(
            tree,
            values[i]);
    }

    double start =
        get_time_seconds();

    for (size_t i = 0; i < size; i++)
    {
        rbtree_search(
            tree,
            values[i]);
    }

    double end =
        get_time_seconds();

    rbtree_destroy(tree);

    return end - start;
}


static double benchmark_delete(
    const int *values,
    size_t size)
{
    RBTree *tree =
        rbtree_create();

    for (size_t i = 0; i < size; i++)
    {
        rbtree_insert(
            tree,
            values[i]);
    }

    double start =
        get_time_seconds();

    for (size_t i = 0; i < size; i++)
    {
        rbtree_delete(
            tree,
            values[i]);
    }

    double end =
        get_time_seconds();

    rbtree_destroy(tree);

    return end - start;
}

void benchmark_run(void)
{

    csv_create("results/results.csv");

    printf("\n");
    printf("========================================\n");
    printf(" RED-BLACK TREE BENCHMARK\n");
    printf("========================================\n\n");

    for (int size_index = 0;
         size_index < NUM_INPUT_SIZES;
         size_index++)
    {
        size_t size =
            INPUT_SIZES[size_index];

        printf("Input Size: %zu\n", size);

        double insert_times[NUM_RUNS];
        double search_times[NUM_RUNS];
        double delete_times[NUM_RUNS];
        int *data =
            generate_random_array(size);

        for (int run = 0;
             run < NUM_RUNS;
             run++)
        {
            insert_times[run] =
                benchmark_insert(
                    data,
                    size);

            search_times[run] =
                benchmark_search(
                    data,
                    size);

            delete_times[run] =
                benchmark_delete(
                    data,
                    size);

            printf(
                "  Run %2d/%d completed\n",
                run + 1,
                NUM_RUNS);
        }

        free(data);

        BenchmarkStats insert_stats =
            benchmark_calculate(
                insert_times,
                NUM_RUNS);

        BenchmarkStats search_stats =
            benchmark_calculate(
                search_times,
                NUM_RUNS);

        BenchmarkStats delete_stats =
            benchmark_calculate(
                delete_times,
                NUM_RUNS);

        printf("\n");

        printf(
            "Insert -> Mean: %.6f s | StdDev: %.6f | Min: %.6f | Max: %.6f\n",
            insert_stats.mean,
            insert_stats.stddev,
            insert_stats.min,
            insert_stats.max);

        printf(
            "Search -> Mean: %.6f s | StdDev: %.6f | Min: %.6f | Max: %.6f\n",
            search_stats.mean,
            search_stats.stddev,
            search_stats.min,
            search_stats.max);

        printf(
            "Delete -> Mean: %.6f s | StdDev: %.6f | Min: %.6f | Max: %.6f\n",
            delete_stats.mean,
            delete_stats.stddev,
            delete_stats.min,
            delete_stats.max);

        printf("\n");

        csv_append_result(
            size,
            insert_stats.mean,
            search_stats.mean,
            delete_stats.mean);
    }

    csv_close();

    printf(
        "\nBenchmark completed successfully.\n");
}

