#ifndef LOGGER_H
#define LOGGER_H

#include <stdbool.h>
#include <stdio.h>

char *fmt(const char *fmt, ...);
int logger_init();
void log_error(char *msg);
void log_info(char *msg);
void log_warning(char *msg);

#endif