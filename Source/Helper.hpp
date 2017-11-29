#ifndef HELPER_HPP
#define HELPER_HPP

#include <cstdint>

static uint32_t trailing_zeros(uint32_t n) {
  if (! n) {
    return -1;
  }

  uint32_t c = 32; // c will be the number of zero bits on the right
  n &= - uint32_t(n);

  if (n) {
    c--;
  }

  if (n & 0x0000FFFF) {
    c -= 16;
  }

  if (n & 0x00FF00FF) {
    c -= 8;
  }

  if (n & 0x0F0F0F0F) {
    c -= 4;
  }

  if (n & 0x33333333) {
    c -= 2;
  }

  if (n & 0x55555555) {
    c -= 1;
  }

  return c;
}

#endif // HELPER_HPP
