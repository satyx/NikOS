#ifndef BASICS_H
#define BASICS_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>

void outb(uint16_t port, uint8_t val);
uint8_t inb(uint16_t port);
#endif