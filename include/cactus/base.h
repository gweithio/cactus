#ifndef BASE_HEADER
#define BASE_HEADER
#include <time.h>
#include <string.h>
#include <log.h>

#define ARRAY_SIZE(Array) (sizeof(Array) / sizeof(Array[0]))

char* time_now() {
  time_t     timer;
  char       buffer[26];
  struct tm* tm_info;
  char*      final;

  timer   = time(NULL);
  tm_info = localtime(&timer);

  strftime(buffer, 26, "%Y-%m-%d", tm_info);

  memmove(final, buffer, strlen(buffer));

  return final;
}

#endif
