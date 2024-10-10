#include <stdio.h>
#include <dlfcn.h>

int main() {
    void* handle = dlopen("../build/libKarnix.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "Failed to load library: %s\n", dlerror());
        return -1;
    }
    printf("Karnix library loaded successfully!\n");

    dlclose(handle);
    return 0;
}
