#include <core/assert.h>
#include <core/log.h>

#define _DBGBREAK __builtin_trap()

void _assert_failed(int line, const char* function, const char* expression, const char* message)
{
    logfmt(LOG_ERROR, function, "Line %d Assertion '%s' failed: %s", line, expression, message);
    _DBGBREAK;
    __builtin_unreachable();
}