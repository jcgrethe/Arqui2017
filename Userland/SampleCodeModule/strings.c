#include "include/strings.h"

int strlen(const char* str) {
  int length = 0;
  while(*str != '\0') {
    str++;
    length++;
  }
  return length;
}