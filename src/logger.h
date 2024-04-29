#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <time.h>

#define CMD_COLOR_LENGTH_STR 8
#define CMD_LOG_LEVEL_LENGTH_STR 17

#define LOG_INFO_STR "LOG_LEVEL_INFO"
#define LOG_WARN_STR "LOG_LEVEL_WARNING"
#define LOG_ERROR_STR "LOG_LEVEL_ERROR"

#define DEFAULT_COLOR "\033[0m"
#define GREEN_COLOR "\x1b[32m"
#define YELLOW_COLOR "\x1b[33m"
#define RED_COLOR "\x1b[31m"

typedef enum {
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR
} LOG_LEVEL;

void log_message(LOG_LEVEL, const char *fmt, ...);

#endif