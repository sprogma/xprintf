#ifndef XPRINTF_H
#define XPRINTF_H

#include "inttypes.h"


/// <summary>
/// 
/// fast and extensible printf realization doesn't supporting floats :)
///
/// </summary>
__attribute__((format(printf, 1, 2)))
int64_t xprintf(const char *format, ...);


__attribute__((format(printf, 2, 3)))
int64_t xsprintf(char *buffer, const char *format, ...);

#endif
