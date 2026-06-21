#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <stddef.h>

#define NUM_RUNS 35

#define NUM_INPUT_SIZES 26


typedef struct
{
    double mean;
    double stddev;
    double min;
    double max;

} BenchmarkStats;


extern const size_t INPUT_SIZES[NUM_INPUT_SIZES];

void benchmark_run(void);

double benchmark_mean(
    const double *values,
    int count);

double benchmark_stddev(
    const double *values,
    int count,
    double mean);

double benchmark_min(
    const double *values,
    int count);

double benchmark_max(
    const double *values,
    int count);

BenchmarkStats benchmark_calculate(
    const double *values,
    int count);

#endif