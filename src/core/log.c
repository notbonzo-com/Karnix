#include <defines.h>
#include <core/log.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

// TODO
// For speed purposes, we can cashe the logs and write them out onto the disk only when they accumulate
// also, dynamic memory is expencie, so we could take a look at that
// FIXME multi-thread mutexes

u8 g_log_type = LOG_TYPE_STDOUT;
const char* g_log_file_name = nullptr;
FILE* g_log_file = nullptr;
static void log_internal(LOG_LEVEL level, const char* function, const char* message);

const char* level_str[] = {"FATAL", "ERROR", "WARN", "INFO", "DEBUG"};
const char* level_color[][3] = {
    {"\033[1;41m", "\033[1;37m", "\033[0m"},
    {"\033[1;31m", "\033[0;37m", "\033[0m"},
    {"\033[1;33m", "\033[0;37m", "\033[0m"},
    {"\033[1;32m", "\033[0;37m", "\033[0m"},
    {"\033[1;34m", "\033[0;37m", "\033[0m"}
};
const char* color_reset = "\033[0m";

static char* format_timestamp() {
    time_t now = time(nullptr);
    struct tm* t = localtime(&now);
    char* buffer = (char*)malloc(64);
    if (buffer && t) {
        if (!strftime(buffer, 64, "%Y-%m-%d %H:%M:%S", t)) {
            if (buffer) free(buffer);
            return nullptr;
        }
    } else {
        if (buffer) free(buffer);
        return nullptr;
    }
    return buffer;
}

b8 init_log(LOG_TYPE type, const char* file_name) {
    g_log_type = type;
    if (type == LOG_TYPE_FILE) {
        g_log_file_name = strdup(file_name);
        if (!g_log_file_name) {
            g_log_type = LOG_TYPE_STDERR;
            log_internal(LOG_ERROR, __func__, "strdup() failed to allocate memory for log file name");
            return false;
        }
        g_log_file = fopen(g_log_file_name, "a");
        if (!g_log_file) {
            g_log_type = LOG_TYPE_STDERR;
            log_internal(LOG_ERROR, __func__, "Failed to open log file");
            return false;
        }
    }
    LOGD("Initialised logging system");
    return true;
}

void term_log(const char* logs_folder) {
    if (g_log_file && g_log_type == LOG_TYPE_FILE) {
        fclose(g_log_file);
        g_log_file = nullptr;

        if (logs_folder && g_log_file_name) {
            struct stat st = {0};
            if (stat(logs_folder, &st) == -1) {
                mkdir(logs_folder, 0700);
            }

            time_t now = time(nullptr);
            struct tm* t = localtime(&now);
            char date_str[64];
            strftime(date_str, sizeof(date_str), "%Y-%m-%d_%H-%M-%S", t);

            size_t path_length = strlen(logs_folder) + strlen(date_str) + strlen(g_log_file_name) + 3;
            char* new_log_file_path = (char*)malloc(path_length);
            if (new_log_file_path) {
                snprintf(new_log_file_path, path_length, "%s/%s-%s", logs_folder, date_str, g_log_file_name);
                if (rename(g_log_file_name, new_log_file_path) != 0) {
                    fprintf(stderr, "Failed to move log file to new location: %s\n", new_log_file_path);
                }
                free(new_log_file_path);
            } else {
                fprintf(stderr, "Failed to allocate memory for new log file path.\n");
            }
        }
    }
    free((void*)g_log_file_name);
    g_log_file_name = nullptr;
}

static char* unknown_time = "unknown_time";
static void log_internal(LOG_LEVEL level, const char* function, const char* message) {
#ifndef _DEBUG
    if (level > LOG_ERROR) return;
#endif
    char* timestamp = nullptr;
    timestamp = format_timestamp();
    if (!timestamp) {
        timestamp = unknown_time;
    }
    if (g_log_type == LOG_TYPE_FILE && g_log_file) {
        fprintf(g_log_file, "[%s] [%s] [%s] %s\n", timestamp, level_str[level], function, message);
        fflush(g_log_file);
    } else if (g_log_type == LOG_TYPE_STDOUT) {
        printf("%s[%s]%s %s[%s]%s %s[%s]%s %s%s\n",
               level_color[level][0], timestamp, color_reset,
               level_color[level][1], level_str[level], color_reset,
               level_color[level][2], function, color_reset,
               message, color_reset);
    } else if (g_log_type == LOG_TYPE_STDERR) {
        fprintf(stderr, "%s[%s]%s %s[%s]%s %s[%s]%s %s%s\n",
                level_color[level][0], timestamp, color_reset,
                level_color[level][1], level_str[level], color_reset,
                level_color[level][2], function, color_reset,
                message, color_reset);
    }           

    if (timestamp != unknown_time) {
        free(timestamp);
    }
}

void logfmt(LOG_LEVEL level, const char* function, const char* format, ...) {
#ifndef _DEBUG
    if (level > LOG_ERROR) return;
#endif

    va_list args;
    va_start(args, format);
    int size = vsnprintf(NULL, 0, format, args) + 1;
    va_end(args);

    char* message = (char*)malloc(size);
    if (!message) {
        log_internal(LOG_ERROR, __func__, "Failed to allocate memory for log message");
        return;
    } else {
        memset(message, 0, size);
    }

    va_start(args, format);
    vsnprintf(message, size, format, args);
    va_end(args);

    log_internal(level, function, message);

    free(message);
}
