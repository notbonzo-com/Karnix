#ifndef _LOG_H
#define _LOG_H

#include <defines.h>

/**
 * If the _DEBUG macro is defined while building, all log levels are enabled.
 * If not defined, only FATAL and ERROR levels will be enabled.
 */
typedef enum {
    LOG_FATAL = 0,  // Fatal error level, indicates a critical issue that prevents program continuation.
    LOG_ERROR = 1,  // Error level, indicates an error that may allow the program to continue.
    LOG_WARN = 2,   // Warning level, indicates a potential issue that should be addressed.
    LOG_INFO = 3,   // Info level, provides general information about the program's operation.
    LOG_DEBUG = 4   // Debug level, used for detailed debugging information.
} LOG_LEVEL;

/**
 * Enum to define the types of logging outputs available.
 */
typedef enum {
    LOG_TYPE_STDOUT = 0, // Log output to standard output (stdout).
    LOG_TYPE_STDERR = 1, // Log output to standard error (stderr).
    LOG_TYPE_FILE = 2    // Log output to a specified file.
} LOG_TYPE;

// Global variable to store the current log level setting.
extern u8 g_log_type;

// Global variable to store the name of the log file when logging to a file.
extern const char* g_log_file_name;

/**
 * @name init_log
 * @brief Initializes the logging system.
 * @param type - The type of logging output to use.
 * @param file_name - The name of the file to log to. nullptr if `type` is not `LOG_TYPE_FILE`.
 * 
 * @returns `true` if successful, `false` otherwise.
 * 
 * @details
 * This function initializes the logging system. It sets the global log level and file name variables.
 * If `type` is `LOG_TYPE_FILE`, it attempts to create the file, ensuring the folder is valid and writable.
 */
b8 init_log(LOG_TYPE type, const char* file_name);

/**
 * @name term_log
 * @brief Closes the logging system and cleans up files.
 * 
 * @details
 * This function closes the logging system, frees allocated memory. If `logs_folder` is not nullptr and
 * `g_log_level` is set to `LOG_TYPE_FILE`, it creates a new date-indexed log file in the given folder 
 * and copies the log file into it, then removes the old log file.
 */
void term_log(const char* logs_folder);

/**
 * @name logf
 * @brief Logs a formatted message with a specific log level.
 * @param level - The log level for the message.
 * @param function - The function name where the log is called.
 * @param format - The format string for the message.
 * @param ... - Additional arguments for the format string.
 */
void logfmt(LOG_LEVEL level, const char* function, const char* format, ...);

// Macros for easier logging
#define LOG(level, format, ...) logfmt(level, __func__, format, ##__VA_ARGS__)
#define LOGF(format, ...) logfmt(LOG_FATAL, __func__, format, ##__VA_ARGS__)
#define LOGW(format, ...) logfmt(LOG_WARN, __func__, format, ##__VA_ARGS__)
#define LOGI(format, ...) logfmt(LOG_INFO, __func__, format, ##__VA_ARGS__)
#define LOGD(format, ...) logfmt(LOG_DEBUG, __func__, format, ##__VA_ARGS__)

#endif // _LOG_H
