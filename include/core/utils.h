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
	char buffer[256];
	struct tm *tm_info;
	char *final = malloc(sizeof(char *));

	timer = time(NULL);
	tm_info = localtime(&timer);

	strftime(buffer, sizeof(buffer), "%Y-%m-%d", tm_info);

	size_t buffer_len = strlen(buffer);
	memmove(final, buffer, buffer_len + 1);

	return final;
}

#endif
