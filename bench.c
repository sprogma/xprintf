#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <locale.h>
#include <x86intrin.h>
#include "xprintf.h"

/// ---- tests

// 1e8
#define MAX_ITERATIONS 100'000'000
#define CHUNK_ITERATIONS 10000
#define WARMUP 1000

#define TESTS \
CREATE_TEST(0, \
    general, \
    some string with diffrent values, \
    3.0, \
    10024, \
    "Loading data: %02d%% completed, %.2e seconds remains. Current task: %-60.60s [...] #%d/%d", \
    12, 3.141592653587276, "Building houses", 18, 1205 \
) \
CREATE_TEST(1, \
    empty call, \
    tests call with empty format buffer, \
    1.0, \
    64, \
    "" \
) \
CREATE_TEST(2, \
    medium parts, \
    tests string with mixed %c and long text parts, \
    2.0, \
    1024, \
    "%cAboba %c AAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAA %c%caaaa%c", \
    'Z', 'Z', 'Z', 'A', 'B', 'C', 'D' \
) \
CREATE_TEST(3, \
    long parts, \
    tests string with mixed %c and long text parts, \
    2.5, \
    20024, \
    "%cAbofjfffffffffffffffffffffffffffffffffffffffffffffff %c AAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAA %c%cAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAaAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuAAAAAAAAAAAAAAAAAAAAAAAAAAAAaaa%c", \
    'Z', 'Z', 'Z', 'A', 'B', 'C', 'D' \
) \
CREATE_TEST(4, \
    group parsing, \
    tests many subsequent %c, \
    3.0, \
    1024, \
    "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", \
    'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z' \
) \
CREATE_TEST(5, \
    bad groups, \
    tests many %c with 1 digit between them, \
    3.0, \
    1024, \
    "X%cX%cX%cX%cX%cX%cX%cX%cX%cX%cX%cX%cX%cX%cX%cX%cX%cX%cX%cX%cX%cX%cX%cX%cX%cX%cX%cX%cX%cX%cX%cX%cX%cX%cX%cX%cX%cX%cX%cX%cX%cX%cX%cX%cX%cX%cX%cX%cX", \
    'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z' \
) \
CREATE_TEST(6, \
    variable width, \
    tests many little paddings at %c, \
    2.0, \
    20124, \
    "%*c%*c%*c%*c%*c%*c%*c%*c%*c%*c%*c%*c%*c%*c%*c%*c%*c%*c%*c%*c%*c%*c%*c%*c%*c%*c%*c%*c%*c%*c%*c", \
    28, 'Z', 21, 'Z', 28, 'Z', 18, 'Z', 28, 'Z', 29, 'Z', 22, 'Z', 25, 'Z', 28, 'Z', 22, 'Z', 28, 'Z', 29, 'Z', 28, 'Z', 29, 'Z', 28, 'Z', 28, 'Z', 28, 'Z', 28, 'Z', 30, 'Z', 28, 'Z', 21, 'Z', 22, 'Z', 28, 'Z', 28, 'Z', 25, 'Z', 28, 'Z', 27, 'Z', 28, 'Z', 27, 'Z', 28, 'Z', 26, 'Z' \
) \
CREATE_TEST(7, \
    little space, \
    tests many little paddings at %c, \
    2.0, \
    20124, \
    "%29c%29c%29c%29c%29c%29c%29c%29c%29c%29c%29c%29c%29c%29c%29c%29c%29c%29c%29c%29c%29c%29c%29c%29c%29c%29c%29c%29c%29c%29c%29c", \
    'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z' \
) \
CREATE_TEST(8, \
    large space, \
    tests very big padding at %c, \
    2.0, \
    20124, \
    "%20000c", \
    'Z' \
) \
CREATE_TEST(9, \
    large zero, \
    tests very big padding by zeroes at %c, \
    2.0, \
    20124, \
    "%020000c", \
    'Z' \
) \
CREATE_TEST(10, \
    little -padd, \
    tests many small negative paddings at %c, \
    2.0, \
    20124, \
    "%-29c%-29c%-29c%-29c%-29c%-29c%-29c%-29c%-29c%-29c%-29c%-29c%-29c%-29c%-29c%-29c%-29c%-29c%-29c%-29c%-29c%-29c%-29c%-29c%-29c%-29c%-29c%-29c%-29c%-29c%-29c", \
    'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z' \
) \
CREATE_TEST(11, \
    large -padd, \
    tests very big negative padding at %c, \
    2.0, \
    20124, \
    "%-20000c", \
    'Z' \
) \
CREATE_TEST(12, \
    empty string-1, \
    tests %.s variant, \
    1.0, \
    1024, \
    "%.s", \
    NULL \
) \
CREATE_TEST(13, \
    empty string-2, \
    tests %.*s variant, \
    1.0, \
    1024, \
    "%.*s", \
    0, \
    NULL \
) \
CREATE_TEST(14, \
    empty string-3, \
    tests %s + "" variant, \
    1.0, \
    1024, \
    "%s", \
    "" \
) \
CREATE_TEST(15, \
    medium string, \
    tests 3-4 of 50-70 character strings, \
    1.5, \
    1024, \
    "%s%s%s", \
    "fooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo", \
    "vaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaar", \
    "oooooooooooooooooooooooooooooooobbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbuu" \
) \
CREATE_TEST(16, \
    large string, \
    tests one large string, \
    2.0, \
    20128, \
    "%s", \
    "fooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooofooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo" \
) \
CREATE_TEST(17, \
    small %float, \
    tests one float string, \
    1.5, \
    1024, \
    "%f", \
    3.14159265358979 \
) \
CREATE_TEST(18, \
    precise %float, \
    tests one float string, \
    1.5, \
    1024, \
    "%.100f", \
    3.14159265358979 \
) \
CREATE_TEST(19, \
    very %float, \
    tests one float string, \
    1.5, \
    6128, \
    "%.5000f", \
    3.14159265358979 \
) \
CREATE_TEST(20, \
    small %e float, \
    tests %e, \
    1.0, \
    1024, \
    "%e", \
    3.14159265358979 \
) \
CREATE_TEST(21, \
    one digit %e, \
    tests %.0e, \
    1.0, \
    1024, \
    "%.0e", \
    3.14159265358979 \
) \
CREATE_TEST(22, \
    normal %e float, \
    tests %.16e, \
    1.0, \
    1024, \
    "%.16e", \
    3.14159265358979 \
) \
CREATE_TEST(23, \
    large %e float, \
    tests %.5000e, \
    1.0, \
    6048, \
    "%.5000e", \
    3.14159265358979 \
) \
CREATE_TEST(24, \
    zero %u, \
    zero %u, \
    1.0, \
    1024, \
    "%u", \
    0 \
) \
CREATE_TEST(25, \
    little %u, \
    little %u, \
    1.0, \
    1024, \
    "%u", \
    179 \
) \
CREATE_TEST(26, \
    medium %u, \
    medium %u, \
    1.0, \
    1024, \
    "%u", \
    998244353 \
) \
CREATE_TEST(27, \
    large %u, \
    large %u, \
    1.0, \
    1024, \
    "%llu", \
    18446744073709551615ull \
) \
CREATE_TEST(28, \
    zero %d, \
    zero %d, \
    1.0, \
    1024, \
    "%d", \
    0 \
) \
CREATE_TEST(29, \
    little %d, \
    little %d, \
    1.0, \
    1024, \
    "%d", \
    179 \
) \
CREATE_TEST(30, \
    medium %d, \
    medium %d, \
    1.0, \
    1024, \
    "%d", \
    998244353 \
) \
CREATE_TEST(31, \
    large %d, \
    large %d, \
    1.0, \
    1024, \
    "%lld", \
    18446744073709551615ull \
) \
CREATE_TEST(32, \
    large %+d, \
    large %+d, \
    1.0, \
    1024, \
    "%+lld", \
    18446744073709551615ull \
) \
CREATE_TEST(33, \
    large %5000d, \
    large %5000d, \
    1.0, \
    6024, \
    "%5000lld", \
    18446744073709551615ull \
) \
CREATE_TEST(34, \
    large %+5000d, \
    large %+5000d, \
    1.0, \
    6024, \
    "%+5000lld", \
    18446744073709551615ull \
) \
CREATE_TEST(35, \
    large %+05000d, \
    large %+05000d, \
    1.0, \
    6024, \
    "%+05000lld", \
    18446744073709551615ull \
) \
CREATE_TEST(36, \
    large %+020d, \
    large %+020d, \
    1.0, \
    6024, \
    "%+020lld", \
    18446744073709551615ull \
) \
CREATE_TEST(37, \
    zero %x, \
    zero %x, \
    1.0, \
    1024, \
    "%x", \
    0 \
) \
CREATE_TEST(38, \
    little %x, \
    little %x, \
    1.0, \
    1024, \
    "%x", \
    179 \
) \
CREATE_TEST(39, \
    medium %x, \
    medium %x, \
    1.0, \
    1024, \
    "%x", \
    998244353 \
) \
CREATE_TEST(40, \
    large %x, \
    large %x, \
    1.0, \
    1024, \
    "%llx", \
    18446744073609551615ull \
) \
CREATE_TEST(41, \
    large %#x, \
    large %#x, \
    1.0, \
    1024, \
    "%#llx", \
    18446744073609551615ull \
) \
CREATE_TEST(42, \
    padded %x, \
    padded %x, \
    1.0, \
    1024, \
    "%08x", \
    998244353 \
) \
CREATE_TEST(43, \
    padded %llx, \
    padded %llx, \
    1.0, \
    1024, \
    "%016llx", \
    18446744073609551615ull \
) \
/**/



/// ---- functions

#define FUNCTIONS(params) \
    FUNCTION(params, 0, xsprintf) \
    FUNCTION(params, 1, sprintf) \
    FUNCTION(params, 2, stbsp_sprintf)


/// -----------------------------------------------------------------------------------------------------------


#define TEST_START(variable) \
    _mm_lfence(); \
    variable = __rdtsc(); \
    _mm_lfence();

#define TEST_END(variable, procid) \
    variable = __rdtscp(&procid); \
    _mm_lfence();
    


uint64_t get_rdtsc_overhead()
{
    #define PROB 5000000
    uint64_t answer = UINT64_MAX, start, end;
    uint32_t procid;
    for (int64_t i = 0; i < PROB; ++i)
    {
        TEST_START(start);
        // ...
        TEST_END(end, procid);
        answer = answer < end - start ? answer : end - start;
    }
    #undef PROB
    return answer;
}


int compare_uint64(const void *a, const void *b) {
    uint64_t arg1 = *(const uint64_t*)a;
    uint64_t arg2 = *(const uint64_t*)b;
    return (arg1 > arg2) - (arg1 < arg2);
}


struct test_result
{
    uint64_t min_cycles;
    uint64_t m50_cycles;
    double avg_time;
};

struct test_result visualizate_results(
    double sys_total_time, // system time measurements [in seconds]
    uint64_t sys_count,
    uint64_t *results, // rdtsc measurements
    uint64_t count,
    uint64_t measured_overhead
)
{
    qsort(results, count, sizeof(*results), compare_uint64);

    double mean = 0.0, dev = 0.0, raw_mean = 0.0, raw_dev = 0.0;
    uint64_t sum = 0, raw_sum = 0;
    for (size_t i = 0; i < count; i++)
    {
        sum += results[i] - measured_overhead;
        raw_sum += results[i];
        double raw_val = (double)results[i];
        double raw_delta = raw_val - raw_mean;
        raw_mean += raw_delta / (i + 1);
        double raw_delta2 = raw_val - raw_mean;
        raw_dev += raw_delta * raw_delta2;
    }

    raw_dev /= count;

    dev = raw_dev;
    mean = raw_mean - measured_overhead;


    printf(" cpu secs:\n");
    printf("   avg call time:        %15.4f ns\n", sys_total_time / sys_count);
    printf("   avg calls/second:  %15.1f m. calls\n", 1e3 * sys_count / sys_total_time);
    printf(" cpu clocks:\n");
    printf("-  min:       %10lu         \033[90m(raw %10lu     )\033[0m\n", results[0] - measured_overhead, results[0]);
    printf("-  med50:     %10lu         \033[90m(raw %10lu     )\033[0m\n", results[count/2] - measured_overhead, results[count/2]);
    printf("-  med90:     %10lu         \033[90m(raw %10lu     )\033[0m\n", results[count*9/10] - measured_overhead, results[count*9/10]);
    printf("~  mean:      %14.3f     \033[90m(raw %14.3f )\033[0m\n", mean, raw_mean);
    printf("~  mean/med:  %12.1f%%      \033[90m(raw %12.1f%%  )\033[0m\n", 100.0 * mean/(results[count/2] - measured_overhead), 100.0 * (raw_mean/results[count/2]));
    printf("~  min/med:   %12.1f%%      \033[90m(raw %12.1f%%  )\033[0m\n", 100.0 * ((double)results[count/2] - measured_overhead)/(results[0] - measured_overhead), 100.0 * ((double)results[count/2]/results[0]));
    printf("~  dev:       %10.3e         \033[90m(raw %10.3e     )\033[0m\n", dev, raw_dev);
    printf(" \033[90m test details: time: %lu ns, %lu cycles;  clocks: %lu (%lu raw) sum, %lu cycles \033[0m\n", (uint64_t)sys_total_time, sys_count, sum, raw_sum, count);

    return (struct test_result){
        .min_cycles = results[0] - measured_overhead,
        .m50_cycles = results[count/2] - measured_overhead,
        .avg_time = sys_total_time / sys_count,
    };
}

#define CREATE_TEST(id, test_name, test_desc, test_time, buffer_size, fmt_string, ...) \
struct test_result test_case ## id (int (*func)(char*, const char*, ...)) \
{ \
    double total_time = test_time * 1e9; char buf[buffer_size]; uint64_t *cycles = malloc(MAX_ITERATIONS * sizeof(*cycles)); \
    struct timespec start, end; unsigned int ui; \
    for (int i = 0; i < WARMUP; i++)  { func(buf, fmt_string __VA_OPT__(,) __VA_ARGS__); } \
    double measured_time = 0.0, cpu_time = 0.0; \
    uint64_t time_iterations = 0, cycle_iterations = 0; \
    while (total_time * 0.5 > measured_time && time_iterations + CHUNK_ITERATIONS < MAX_ITERATIONS) \
    { \
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start); \
        for (int i = 0; i < CHUNK_ITERATIONS; i++)  { func(buf, fmt_string __VA_OPT__(,) __VA_ARGS__); } \
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end); \
        time_iterations += CHUNK_ITERATIONS; \
        double dtime = (end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec); \
        cpu_time += dtime; \
        measured_time += dtime; \
    } \
    measured_time = 0.0; \
    while (total_time * 0.5 > measured_time && cycle_iterations + CHUNK_ITERATIONS < MAX_ITERATIONS) \
    { \
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start); \
        uint64_t base = cycle_iterations, t1, t2; \
        for (int i = 0; i < CHUNK_ITERATIONS; i++)  \
        { \
            TEST_START(t1); \
            func(buf, fmt_string __VA_OPT__(,) __VA_ARGS__); \
            TEST_END(t2, ui); \
            cycles[base+i] = t2 - t1; \
        } \
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end); \
        cycle_iterations += CHUNK_ITERATIONS; \
        measured_time += (end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec); \
    } \
    struct test_result res = visualizate_results(cpu_time, time_iterations, cycles, cycle_iterations, get_rdtsc_overhead()); \
    free(cycles); \
    return res; \
}

TESTS

#undef CREATE_TEST

#define STB_SPRINTF_IMPLEMENTATION 
#include "stb_sprintf.h"

void test(int no_comparison)
{
    printf("---- gathering cpu information ----\n");
    uint64_t timer_overhead = get_rdtsc_overhead();
    printf("min loop overhead: %lu\n", timer_overhead);

    struct test_result res[1024*64];

    #define FUNCTION(params, xid, x) \
        if (!no_comparison || xid == 0) { \
            puts("---- testing function " #x); \
            res[params * 64 + xid] = test_case ## params((int (*)(char *, const char *, ...))(void *)x); \
        }

    #define CREATE_TEST(id, test_name, test_desc, ...) \
        puts("\n\n\n --------------------------------------- " #test_name " ---------------------------------------- "); \
        puts("    " #test_desc); \
        FUNCTIONS(id)

    TESTS

    #undef CREATE_TEST
    #undef FUNCTION

    const char* func_names[] = {
        #define FUNCTION(id, xid, x) #x,
        FUNCTIONS(0)
        #undef FUNCTION
    };

    uint64_t func_scores_min[] = {
        #define FUNCTION(id, xid, x) 0,
        FUNCTIONS(0)
        #undef FUNCTION
    };

    uint64_t func_scores_m50[] = {
        #define FUNCTION(id, xid, x) 0,
        FUNCTIONS(0)
        #undef FUNCTION
    };

    double func_scores_avg[] = {
        #define FUNCTION(id, xid, x) 0.0,
        FUNCTIONS(0)
        #undef FUNCTION
    };

    uint32_t func_medals[][3] = {
        #define FUNCTION(id, xid, x) {},
        FUNCTIONS(0)
        #undef FUNCTION
    };

    double best_values[][3] = {
        #define CREATE_TEST(...) {1e300, 1e300, 1e300},
        TESTS
        #undef CREATE_TEST
    };

    const int SS = 4;
    
    int num_funcs = sizeof(func_names) / sizeof(func_names[0]);

    if (no_comparison)
    {
        num_funcs = 1;
    }
    
    int test_count = 0;
    #define CREATE_TEST(id, ...) test_count++;
    TESTS
    #undef CREATE_TEST

    for (int t = 0; t < test_count; ++t)
    {
        for (int f = 0; f < num_funcs; ++f)
        {
            best_values[t][0] = best_values[t][0] < res[t * 64 + f].min_cycles ? best_values[t][0] : res[t * 64 + f].min_cycles;
            best_values[t][1] = best_values[t][1] < res[t * 64 + f].m50_cycles ? best_values[t][1] : res[t * 64 + f].m50_cycles;
            best_values[t][2] = best_values[t][2] < res[t * 64 + f].avg_time ? best_values[t][2] : res[t * 64 + f].avg_time;
        }
    }

    for (int base = 0; base < test_count; base += SS)
    {
        printf("\n\n| %-26s |", "Realization \\ Test");
        #define CREATE_TEST(id, name, ...) \
            if (base <= id && id < base + SS) { \
                printf(" %-15s |", #name); }
        TESTS
        #undef CREATE_TEST
        printf("\n");
        
        printf("\n");
        for (int f = 0; f < num_funcs; f++) 
        {
            #define START_COLOR(id) \
                if (res[id * 64 + 0].min_cycles <= best_values[id][0] && \
                    res[id * 64 + 0].m50_cycles <= best_values[id][1] && \
                    res[id * 64 + 0].avg_time <= best_values[id][2]) \
                { \
                    printf("\x1b[48;2;0;70;0m"); \
                } \
                else if (res[id * 64 + 0].min_cycles <= best_values[id][0] || \
                         res[id * 64 + 0].m50_cycles <= best_values[id][1] || \
                         res[id * 64 + 0].avg_time <= best_values[id][2]) \
                { \
                    printf("\x1b[48;2;60;60;0m"); \
                } \
                else \
                { \
                    printf("\x1b[48;2;70;0;0m"); \
                }

            #define END_COLOR \
                printf("\x1b[0m");
            
            if (base == 0)
            {
                printf("|----------------------------|");
                #define CREATE_TEST(id, ...) \
                    if (base <= id && id < base + SS) { START_COLOR(id) \
                        printf("-----------------|"); END_COLOR }
                TESTS
                #undef CREATE_TEST
            }
            
            printf("| %-15s min cycles |", func_names[f]);
            #define CREATE_TEST(id, ...) \
                if (base <= id && id < base + SS) { START_COLOR(id) \
                    printf(" %11lu     |", res[id * 64 + f].min_cycles); \
                    func_scores_min[f] += res[id * 64 + f].min_cycles; \
                    func_medals[f][0] += res[id * 64 + f].min_cycles <= best_values[id][0]; END_COLOR }
            TESTS
            #undef CREATE_TEST
            printf("\n");
        
            printf("| %-15s m50 cycles |", "");
            #define CREATE_TEST(id, ...) \
                if (base <= id && id < base + SS) { START_COLOR(id) \
                    printf(" %11lu     |", res[id * 64 + f].m50_cycles); \
                    func_scores_m50[f] += res[id * 64 + f].m50_cycles; \
                    func_medals[f][1] += res[id * 64 + f].m50_cycles <= best_values[id][1]; END_COLOR }
            TESTS
            #undef CREATE_TEST
            printf("\n");
        
            printf("| %-15s avg time   |", "");
            #define CREATE_TEST(id, ...) \
                if (base <= id && id < base + SS) { START_COLOR(id) \
                    printf(" %12.3f ns |", res[id * 64 + f].avg_time); \
                    func_scores_avg[f] += res[id * 64 + f].avg_time; \
                    func_medals[f][2] += res[id * 64 + f].avg_time <= best_values[id][2]; END_COLOR }
            TESTS
            #undef CREATE_TEST
            printf("\n");
        
            printf("|----------------------------|");
            #define CREATE_TEST(id, ...) \
                if (base <= id && id < base + SS) { START_COLOR(id) \
                    printf("-----------------|"); END_COLOR }
            TESTS
            #undef CREATE_TEST
            printf("\n");
        }
    }

    uint64_t best_score_min = UINT64_MAX / 4, best_score_m50 = UINT64_MAX / 4;
    FILE *f = fopen("best_score.txt", "r");
    if (f != NULL)
    {
        fscanf(f, "%lu %lu", &best_score_min, &best_score_m50);
        fclose(f);
        if (best_score_min == 0)
        {
            best_score_min = UINT64_MAX / 4;
        }
        if (best_score_m50 == 0)
        {
            best_score_m50 = UINT64_MAX / 4;
        }
    }

    for (int f = 0; f < num_funcs; ++f)
    {
        printf("function %-20s scored:\n", func_names[f]);
        printf("        %3d medals in category min_cycles\n", func_medals[f][0]);
        printf("        %3d medals in category m50_cycles\n", func_medals[f][1]);
        printf("        %3d medals in category avg_time\n", func_medals[f][2]);
    }

    printf("\nFunction scores: [min]\n");
    for (int f = 0; f < num_funcs; ++f)
    {
        printf("  %-20s: %10lu [%+10ld] %s\n", func_names[f], func_scores_min[f], func_scores_min[f] - best_score_min, best_score_min < func_scores_min[f] ? "" : "better!");
    }
    printf("Function scores: [m50]\n");
    for (int f = 0; f < num_funcs; ++f)
    {
        printf("  %-20s: %10lu [%+10ld] %s\n", func_names[f], func_scores_m50[f], func_scores_m50[f] - best_score_m50, best_score_m50 < func_scores_m50[f] ? "" : "better!");
    }
    printf("Function scores: [avg]\n");
    for (int f = 0; f < num_funcs; ++f)
    {
        printf("  %-20s: %12.2f ns\n", func_names[f], func_scores_avg[f]);
    }
    printf("\n");

    uint64_t old_min = best_score_min, old_m50 = best_score_m50;

    for (int f = 0; f < num_funcs; ++f)
    {
        best_score_min = best_score_min < func_scores_min[f] ? best_score_min : func_scores_min[f];
        best_score_m50 = best_score_m50 < func_scores_m50[f] ? best_score_m50 : func_scores_m50[f];
    }

    uint32_t copy = 0;

    if (best_score_min != old_min && best_score_min == func_scores_min[0]) // our function
    {
        copy = 1;
    }
    if (best_score_m50 != old_m50 && best_score_m50 == func_scores_m50[0]) // our function
    {
        copy = 1;
    }

    if (copy)
    {
        printf("Got new best result!\n");
        const char *cmd = "find ./src -type f -exec sha256sum {} + | awk '{print $1}' | sort | sha256sum";
        char hash[17]; // first 16 chars
        FILE *fp;
        fp = popen(cmd, "r");
        if (fp == NULL) 
        {
            perror("Error at running");
            exit(1);
        }
        if (fgets(hash, sizeof(hash), fp) != NULL) 
        {
            printf("resulting in hash: %s\n", hash);
        }
        pclose(fp);    
        char command[128];
        sprintf(command, "cp -r src ./best/%lu_%lu____%s", func_scores_min[0], func_scores_m50[0], hash);
        system(command);
    }
    
    f = fopen("best_score.txt", "w");
    fprintf(f, "%lu %lu", best_score_min, best_score_m50);
    fclose(f);
}

int main(int argc, const char **argv) 
{
    int one = 0;
    for (int i = 1; i < argc; ++i)
    {
        if (strcmp(argv[i], "-no-comparison") == 0)
        {
            one = 1;
        }
    }
    test(one);
    return 0;
}
