#ifndef CONVERSIONS_H
#define CONVERSIONS_H

#include <cstdint>
#include "Constants.h"


// function to convert from bytes to kilo bytes
template <typename T>
static inline uintmax_t convertToKB(T bytes)
{
    return static_cast<unsigned long long>(bytes / kILO);
}

// function to convert from bytes to Mega bytes
template <typename T>
static inline uintmax_t convertToMB(T bytes)
{
    return static_cast<unsigned long long>(bytes / MEGA);
}

// function to convert from bytes to giga bytes
template <typename T>
static inline uintmax_t convertToGB(T bytes)
{
    return static_cast<unsigned long long>(bytes / GIGA);
}
#endif // CONVERSIONS_H
