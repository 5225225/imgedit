#pragma once
#define CLAMP(x, low, high) ({\
  __typeof__(x) __CLAMP_x = (x); \
  __typeof__(low) __CLAMP_low = (low);\
  __typeof__(high) __CLAMP_high = (high);\
  __CLAMP_x > __CLAMP_high ? __CLAMP_high : (__CLAMP_x < __CLAMP_low ? __CLAMP_low : __CLAMP_x);\
  })
