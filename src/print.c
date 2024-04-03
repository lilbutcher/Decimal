#include <limits.h>
#include <stdio.h>

#include "s21_decimal.h"

#define bindump(ptr, size)                       \
  ({                                             \
    unsigned long n = (size)*CHAR_BIT;           \
    while (n) printf("%d", (*(ptr) >> --n) & 1); \
  })

void s21_decimal_print(s21_decimal value) {
  bindump(&value.bits[3], sizeof(unsigned int));
  bindump(&value.bits[2], sizeof(unsigned int));
  bindump(&value.bits[1], sizeof(unsigned int));
  bindump(&value.bits[0], sizeof(unsigned int));
}

void s21_big_decimal_print(s21_big_decimal value) {
  bindump(&value.decimals[1].bits[3], sizeof(unsigned int));
  bindump(&value.decimals[1].bits[2], sizeof(unsigned int));
  bindump(&value.decimals[1].bits[1], sizeof(unsigned int));
  bindump(&value.decimals[1].bits[0], sizeof(unsigned int));
  bindump(&value.decimals[0].bits[3], sizeof(unsigned int));
  bindump(&value.decimals[0].bits[2], sizeof(unsigned int));
  bindump(&value.decimals[0].bits[1], sizeof(unsigned int));
  bindump(&value.decimals[0].bits[0], sizeof(unsigned int));
}