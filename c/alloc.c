#include "alloc.h"

void* malloc_exit(size_t size) {
    void* ret = malloc(size);
    if(ret == NULL) exit(1);
    return ret;
}
