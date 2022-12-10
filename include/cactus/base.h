#ifndef BASE_HEADER
#define BASE_HEADER
#include <log.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define ARRAY_SIZE(Array) (sizeof(Array) / sizeof(Array[0]))

char *
time_now()
{
  time_t t = time(NULL);
  struct tm *tm = localtime(&t);
  char s[64];
  char *final;

  return asctime(tm);
}

#endif
