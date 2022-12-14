#ifndef UTILS_HEADER
#define UTILS_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ARRAY_SIZE(Array) (sizeof(Array) / sizeof(Array[0]))

char *time_now()
{
	time_t timer;
	char buffer[26];
	struct tm *tm_info;
	char *final;

	timer = time(NULL);
	tm_info = localtime(&timer);

	strftime(buffer, 26, "%Y-%m-%d", tm_info);

	memmove(final, buffer, strlen(buffer) + strlen(final));

	return final;
}

#endif
