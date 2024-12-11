#include "logger.h"
#include <stdarg.h>
#include <stdlib.h>

int logger_enabled = 0;

char *fmt(const char *fmt, ...) {
  va_list args;
  va_list args_copy;
  int len;
  char *msg;

  // Start argument processing
  va_start(args, fmt);

  // Make a copy of args for later reuse
  va_copy(args_copy, args);

  // Get the required length for the formatted string
  len = vsnprintf(NULL, 0, fmt, args_copy);
  va_end(args_copy);

  if (len < 0) {
    // Error in vsnprintf (invalid format or other issues)
    va_end(args);
    return NULL;
  }

  // Allocate memory for the formatted string (+1 for null terminator)
  msg = (char *)malloc(len + 1);
  if (msg == NULL) {
    // Memory allocation failed
    va_end(args);
    return NULL;
  }

  // Now actually format the string into the allocated memory
  if (vsnprintf(msg, len + 1, fmt, args) < 0) {
    // Error in vsnprintf
    free(msg); // Free the allocated memory before returning
    va_end(args);
    return NULL;
  }

  // End argument processing
  va_end(args);

  return msg;
}

int logger_init() {
  logger_enabled = 1;
  printf("Logger initialised...\n");
  return 0;
}

void log_info(char *message) {
  if (logger_enabled)
    printf("\033[92m Info: %s \033[0m\n", message);
}

void log_error(char *message) {
  fprintf(stderr, "\033[95m Error: %s \033[0m\n", message);
}

void log_warning(char *message) {
  if (logger_enabled)
    fprintf(stderr, "\033[93m Warning: %s \033[0m\n", message);
}
