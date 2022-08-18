#ifndef BASE_HEADER
#define BASE_HEADER
#include <time.h>
#include <string.h>
#include <log.h>

#define ARRAY_SIZE(Array) (sizeof(Array) / sizeof(Array[0]))

const char* current_time() {
  time_t     rawtime;
  struct tm* timeinfo;
  char*      time_string = NULL;
  time(&rawtime);
  timeinfo = localtime(&rawtime);

  strftime(time_string, strlen(time_string), "%Y-%m-%d", timeinfo);

  return time_string;
}

#endif
