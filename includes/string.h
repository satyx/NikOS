#ifndef STRING_H
#define STRING_H
#include <stddef.h>
#include <stdint.h>

size_t strlen(const char*);
void memset(void*, int, size_t);
void memcpy(void*, void*, size_t);

#endif