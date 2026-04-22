#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <x86intrin.h> // Интринсики для x86
#include "xprintf.h"

#define ITERATIONS 10000000
#define WARMUP 100000

#define FMT_STRING "%cAboba %c AAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAA %c%caaaa%c"
#define FMT_DATA 'Z', 'Z', 'Z', 'A', 'B', 'C', 'D'

int compare_uint64(const void *a, const void *b) {
    uint64_t arg1 = *(const uint64_t*)a;
    uint64_t arg2 = *(const uint64_t*)b;
    return (arg1 > arg2) - (arg1 < arg2);
}

void run_test(const char* name, int (*func)(char*, const char*, ...)) {
    char buf[1024];
    uint64_t *cycles = malloc(ITERATIONS * sizeof(uint64_t));
    struct timespec start, end;
    unsigned int ui;

    for(int i = 0; i < WARMUP; i++) {
        func(buf, FMT_STRING, FMT_DATA);
    }

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
    for(int i = 0; i < ITERATIONS; i++) {
        func(buf, FMT_STRING, FMT_DATA);
    }
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);

    double cpu_time_used = (end.tv_sec - start.tv_sec) + 
                           (end.tv_nsec - start.tv_nsec) / 1e9;

    for(int i = 0; i < ITERATIONS; i++) {
        uint64_t t1 = __rdtscp(&ui);
        func(buf, FMT_STRING, FMT_DATA);
        uint64_t t2 = __rdtscp(&ui);
        cycles[i] = t2 - t1;
    }

    qsort(cycles, ITERATIONS, sizeof(uint64_t), compare_uint64);

    printf("Example output:\n");
    puts(buf);

    printf("--- %s ---\n", name);
    printf("Total CPU Time:  %.6f s\n", cpu_time_used);
    printf("RDTSC Min:       %lu cycles\n", cycles[0]);
    printf("RDTSC P50 (Med): %lu cycles\n", cycles[ITERATIONS / 2]);
    printf("RDTSC P90 (Med): %lu cycles\n", cycles[(int)(ITERATIONS * 0.9)]);
    printf("\n");

    free(cycles);
}

#define STB_SPRINTF_IMPLEMENTATION 
#include "stb_sprintf.h"

int main() {
    run_test("Standard sprintf", sprintf);
    run_test("xsprintf", (int (*)(char*, const char*, ...))(void *)xsprintf);
    run_test("stbsp_sprintf", (int (*)(char*, const char*, ...))(void *)stbsp_sprintf);
    return 0;
}
