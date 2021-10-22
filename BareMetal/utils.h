#ifndef UTILS_H
#define UTILS_H

#include <string.h>
#include <stdint.h>

void strrev(char* str);
size_t strlen(const char* str);
void itoa(char* dst, uint32_t x);

#endif