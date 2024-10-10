#include <stdio.h>
#include <dlfcn.h>
#include <defines.h>

#include <core/log.h>
#include <core/assert.h>

int main(int, char*[]) {
    init_log(LOG_TYPE_STDOUT, nullptr);

    term_log(nullptr);
    return 0;
}
