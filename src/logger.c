#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "logger.h"

time_t current_sys_time;
struct tm * localtime_sys;

static void get_system_time() {
    time(&current_sys_time);
    localtime_sys = localtime(&current_sys_time);
}

void log_message(LOG_LEVEL log_level, const char *fmt, ...) {
    size_t color_str_size = CMD_COLOR_LENGTH_STR * sizeof(char);
    size_t log_level_str = CMD_LOG_LEVEL_LENGTH_STR * sizeof(char);

    char *log_color = (char *) malloc(color_str_size);
    char *log_level_type = (char *) malloc(log_level_str);
    get_system_time();

    switch (log_level)
    {
    case LOG_INFO:
        memcpy(log_color, GREEN_COLOR, color_str_size);
        memcpy(log_level_type, LOG_INFO_STR, log_level_str);
        break;
    case LOG_WARNING:
        memcpy(log_color, YELLOW_COLOR, color_str_size);
        memcpy(log_level_type, LOG_WARN_STR, log_level_str);
        break;
    case LOG_ERROR:
        memcpy(log_color, RED_COLOR, color_str_size);
        memcpy(log_level_type, LOG_ERROR_STR, log_level_str);
        break;
    default:
        break;
    }

    printf("[%s%s%s][%d/%d/%d %d:%d:%d]: ", log_color, log_level_type, DEFAULT_COLOR,
        localtime_sys -> tm_mday, localtime_sys -> tm_mon,
        localtime_sys -> tm_year + 1900, localtime_sys -> tm_hour, 
        localtime_sys -> tm_min, localtime_sys -> tm_sec); 
    
    va_list args;

    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);

    free(log_color);
    free(log_level_type);    
}
