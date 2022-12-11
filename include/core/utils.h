#ifndef UTILS_HEADER
#define UTILS_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ARRAY_SIZE(Array) (sizeof(Array) / sizeof(Array[0]))

#if 0
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

char *
time_now()
{
  time_t timer;
  char buffer[26];
  struct tm *tm_info;
  char *final = malloc(10 * sizeof(char));

  if (!final)
    return NULL;

  timer = time(NULL);
  tm_info = localtime(&timer);

  strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);

  memmove(final, buffer, strlen(final) * strlen(buffer) + 1);

  return final;
}

#endif
