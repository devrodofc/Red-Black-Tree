#include <stdio.h>

#include "../include/benchmark.h"

int main(void)
{
    printf("========================================\n");
    printf(" Red-Black Tree Performance Benchmark\n");
    printf("========================================\n\n");

    benchmark_run();

    printf("\n");
    printf("Results saved successfully.\n");
    printf("Execution finished.\n");

    return 0;
}